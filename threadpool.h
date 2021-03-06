//线程池的类
template<typename T>
class threadpool{
    public:
        //构造函数
        threadpool(connection_pool* connPool,int thread_number=8,int max_request = 10000);
        //系够函数
        ~threadpool();
        //reactor增加
        bool append_r(T* request,int state);
        //proactor增加
        bool append_p(T* request);

    private:
        //进入工作模式
        static void* worker(void* arg);
        //真正处理
        void run(); 

    private:
        int m_thread_number; //线程池数
        int m_max_requesets; //请求队列最大请求数
        pthread_t *m_threads;//线程池数组 
        std::list<T *>m_workqueue;//请求队列
        locker m_queuelocker;//队列的互斥锁
        sem m_queuestate;//任务处理信号
        bool m_stop;//是否结束线程
        connection_pool *m_connPool;//数据库连接池
} 

//构造函数
template<typename T>
threadpool<T>::threadpool(connection_pool *connPool,int thread_number,int max_requests) : m_thread_number(thread_number),m_max_requests(max_requests),m_stop(false),m_thread(NULL),m_connPool(connPool){
    if(thread_number<=0||max_requests<=0)
        throw std::exception();
    
    //线程池id初始化
    m_threads = new pthread_t[m_thread_nubmer];
    if(!m_threads)
        throw std::exception();

    for(int i = 0;i<thread_number;++i){
        //创建线程
        if(pthread_create(m_threads+i,NULL,worker,this)!=0){
            delete[] m_threads;
            throw std::exception();
        }

        //线程进行分离
        if(pthread_detach(m_threads[i]){
            delete[] m_threads; 
            throw std::exception();
        }
    } 
}



//系够函数
template<typename T>
threadpool<T>::~threadpool(){
    delete[] m_threads;
}

//Reactor放入队列
tmplate<typename T>
bool threadpool<T>::append_r(T* request,int state){
    //上锁
    m_queuelock.lock();
    if(m_workqueue.size()>m_max_requests){
        m_queuelocker.unlock();
        return false;
    } 

    request->m_state = state;


    //添加任务并解锁
    m_workqueue.push_back(request);
    m_queuelocker.unlock();

    //发送信号
    m_queuestate.post();
    return true; 
}

//Proactor放入队列
tmplate<typename T>
bool threadpool<T>::append_r(T* request){
    //上锁
    m_queuelock.lock();
    if(m_workqueue.size()>m_max_requests){
        m_queuelocker.unlock();
        return false;
    } 

    //添加任务并解锁
    m_workqueue.push_back(request);
    m_queuelocker.unlock();

    //发送信号
    m_queuestate.post();
    return true; 
}

//进入工作模式
template<typename T>
void* threadpool<T>::worker(void *arg){
    //将参数强转为线程池类,调用成员方法
    threadpool *pool = (threadpool*) arg;
    pool->run();
    return pool;
}

//真正处理
template<typename T>
void thread<T>::run(){
    while(true)
    {
        //信号量等待
        m_queuestate.wait();

        //被唤醒后先加互斥锁
        m_queuelocker.lock();
        if(m_workqueue.empty())
        {
            m_queuelocker.unlock();
            continue;
        }

        //取出任务
        T* request = m_workqueue.front();
        m_workqueue.pop_front();
        m_queuelocker.unlock();
        if(!request)
            continue;

        //reactor
        if(1 == m_actor_model)
        {
            //读
            if(0 == request->m_state)
            {
                //成功读没有
                if(request->read_once())
                {
                    //成功读了
                    request->improv = 1;
                    //获取数据库连接
                    connectionRAII mysqlcon(&request->mysql,m_connPool);
                    //调用process处理
                    request->process(); 
                }
                else
                {
                    //未能成功读
                    request->improv = 1;
                    request->timer_flag = 1;
                }

            }

            //写
            else
            {
                //成功发没有
                if(request->write())
                {
                    request->improv = 1;
                }
                else
                {
                    request->improv = 1;
                    request->timer_flag = 1;
                }
            }
        }
        
        //proactor
        {
            //获取数据库连接
            connectionRAII mysqlcon(&request->mysql,m_connPool);
            //调用process
            request->process();
        }


    }
}
