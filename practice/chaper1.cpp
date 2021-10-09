#include <iostream>
#include <string>
#include "Sales_data.h"
using namespace std;
int main(){
    Sale_data book1,book2;
    double price1,price2;
    std::cin>>book1.bookNo>>book1.units_sold>>price1;
    std::cin>>book2.bookNo>>book2.units_sold>>price2;
    book1.revenue=book1.units_sold*price1;
    book2.revenue=book2.units_sold*price2;
    std::cout<<"++++++++++++++++++++++"<<std::endl;
    std::cout<<"book1 no units price"<<std::endl;
    std::cout<<book1.bookNo<<" "<<book1.units_sold<<" "<<price1<<std::endl;
    std::cout<<"++++++++++++++++++++++"<<std::endl;
    std::cout<<"book2 no units price"<<std::endl;
    std::cout<<book2.bookNo<<" "<<book2.units_sold<<" "<<price2<<std::endl;
    if(book1.bookNo==book2.bookNo){
        unsigned total_unit = book1.units_sold +book2.units_sold;
        double totalRevenue = book1.revenue + book2.revenue;
        std::cout<<"book total_unit=="<<total_unit<<std::endl;
        std::cout<<"book total revenue=="<<totalRevenue<<std::endl;
    }
    else{
        std::cout<<"it's not the same book"<<std::endl;
    } 




    return 0;

}

