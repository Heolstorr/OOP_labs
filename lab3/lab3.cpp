#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>

using namespace std;

class ElectricityBook {
private:
    string date;
    double costPerKWh;
    double paidAmount;
    int meterReading;

public:
    ElectricityBook() {
        date = "1970-01-01";
        costPerKWh = 0.0;
        paidAmount = 0.0;
        meterReading = 0;
    }

    ElectricityBook(string d, double cost, double paid, int reading) {
        setDate(d);
        setCostPerKWh(cost);
        setPaidAmount(paid);
        setMeterReading(reading);
    }

    void setDate(string d) {
        if (d.empty()) {
            throw invalid_argument("Date cannot be empty.");
        }
        date = d;
    }

    void setCostPerKWh(double cost) {
        if (cost < 0) {
            throw invalid_argument("Cost per kWh cannot be negative.");
        }
        costPerKWh = cost;
    }

    void setPaidAmount(double paid) {
        if (paid < 0) {
            throw invalid_argument("Paid amount cannot be negative.");
        }
        paidAmount = paid;
    }

    void setMeterReading(int reading) {
        if (reading < 0) {
            throw invalid_argument("Meter reading cannot be negative.");
        }
        meterReading = reading;
    }

    string getDate() const { return date; }
    
    double getCostPerKWh() const { 
        if (costPerKWh == 0.0) {
            throw logic_error("Cost is not set properly.");
        }
        return costPerKWh; 
    }
    
    double getPaidAmount() const { return paidAmount; }
    int getMeterReading() const { return meterReading; }

    ElectricityBook& operator++() {
        meterReading++;
        return *this;
    }

    ElectricityBook operator++(int) {
        ElectricityBook temp = *this;
        meterReading++;
        return temp;
    }

    ElectricityBook& operator--() {
        if (meterReading - 1 < 0) {
            throw out_of_range("Meter reading cannot fall below zero.");
        }
        meterReading--;
        return *this;
    }

    ElectricityBook operator--(int) {
        ElectricityBook temp = *this;
        if (meterReading - 1 < 0) {
            throw out_of_range("Meter reading cannot fall below zero.");
        }
        meterReading--;
        return temp;
    }

    ElectricityBook& operator-=(int value) {
        if (meterReading - value < 0) {
            throw out_of_range("Meter reading cannot fall below zero.");
        }
        meterReading -= value;
        return *this;
    }

    void print() const {
        cout << "Date: " << setw(12) << left << date
             << " | Reading: " << setw(6) << meterReading
             << " | Cost/kWh: " << setw(6) << costPerKWh
             << " | Paid: " << paidAmount << "\n";
    }
};

class BookManager {
private:
    vector<ElectricityBook> records;
public:
    void addRecord(const ElectricityBook& record) {
        records.push_back(record);
    }

    void searchByDate(string date) const {
        bool found = false;
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].getDate() == date) {
                records[i].print();
                found = true;
            }
        }
        if (!found) cout << "No records found for date: " << date << "\n";
    }

    void searchByDate(string startDate, string endDate) const {
        bool found = false;
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].getDate() >= startDate && records[i].getDate() <= endDate) {
                records[i].print();
                found = true;
            }
        }
        if (!found) cout << "No records found in range: " << startDate << " - " << endDate << "\n";
    }
};

int main() {
    BookManager manager;

    try {
        ElectricityBook b1("2026-09-01", 2.64, 500.0, 15200);
        ElectricityBook b2("2026-10-01", 2.64, 650.0, 15450);
        
        manager.addRecord(b1);
        manager.addRecord(b2);

        cout << "Initial records:\n";
        b1.print();
        b2.print();
        cout << "\n";

        ++b1;
        b2++;
        
        cout << "After operator++ :\n";
        b1.print();
        b2.print();
        cout << "\n";

        --b1;
        b2 -= 50;

        cout << "After decrement operations :\n";
        b1.print();
        b2.print();
        cout << "\n";

        cout << "Search with 1 parameter:\n";
        manager.searchByDate("2026-10-01");
        cout << "\n";

        cout << "Search with 2 parameters (overloaded):\n";
        manager.searchByDate("2026-09-01", "2026-10-31");
        cout << "\n";

        cout << "Testing exceptions:\n";
        ElectricityBook b3;
        b3.setPaidAmount(-100.0); 

    } catch (const invalid_argument& e) {
        cout << "Invalid Argument Exception: " << e.what() << "\n";
    } catch (const out_of_range& e) {
        cout << "Out of Range Exception: " << e.what() << "\n";
    } catch (const exception& e) {
        cout << "General Exception: " << e.what() << "\n";
    }

    return 0;
}