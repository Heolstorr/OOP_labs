#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

class Ingredient {
private:
    string name;
    double amount;
    double pricePerUnit;

public:
    Ingredient() {
        name = "Unknown";
        amount = 0.0;
        pricePerUnit = 0.0;
    }

    Ingredient(string n, double a, double p) {
        name = n;
        amount = a;
        pricePerUnit = p;
    }

    void set(string n, double a, double p) {
        name = n;
        amount = a;
        pricePerUnit = p;
    }

    string getName() const { return name; }
    double getAmount() const { return amount; }
    double getPricePerUnit() const { return pricePerUnit; }

    double getCost() const {
        return amount * pricePerUnit;
    }

    void show() const {
        cout << left << setw(25) << name 
             << " Amount: " << setw(8) << amount 
             << " Price/Unit: " << setw(8) << pricePerUnit 
             << " Cost: " << getCost() << "\n";
    }
};

class Recipe {
private:
    string recipeName;
    vector<Ingredient> ingredients;

public:
    Recipe() {
        recipeName = "Untitled";
    }

    Recipe(string name) {
        recipeName = name;
    }

    void set(string name) {
        recipeName = name;
    }

    string getRecipeName() const { return recipeName; }

    void addIngredient(Ingredient ing) {
        ingredients.push_back(ing);
    }

    double getTotalCost() const {
        double total = 0.0;
        for (size_t i = 0; i < ingredients.size(); i++) {
            total += ingredients[i].getCost();
        }
        return total;
    }

    void show() const {
        cout << "Recipe: " << recipeName << "\n";
        for (size_t i = 0; i < ingredients.size(); i++) {
            ingredients[i].show();
        }
        cout << "Total Recipe Cost: " << getTotalCost() << "\n\n";
    }

    void saveToFile(string filename) const {
        ofstream file(filename, ios::app);
        
        if (!file.is_open()) {
            cerr << "Error: Cannot open file for saving.\n";
            return;
        }

        file << recipeName << "\n";
        file << ingredients.size() << "\n";
        
        for (size_t i = 0; i < ingredients.size(); i++) {
            file << ingredients[i].getName() << "\n";
            file << ingredients[i].getAmount() << "\n";
            file << ingredients[i].getPricePerUnit() << "\n";
        }
        
        file.close();
        cout << "Recipe '" << recipeName << "' successfully saved to " << filename << ".\n\n";
    }

    static void findRecipe(string filename, string searchName) {
        ifstream file(filename);
        
        if (!file.is_open()) {
            cerr << "Error: Cannot open file for reading.\n";
            return;
        }

        string currentRecipeName;
        
        while (getline(file, currentRecipeName)) {
            string sizeStr;
            getline(file, sizeStr);
            int numIngredients = stoi(sizeStr); 

            if (currentRecipeName == searchName) {
                cout << "Recipe '" << searchName << "' found in database.\n";
                
                Recipe foundRecipe(currentRecipeName);
                
                for (int i = 0; i < numIngredients; i++) {
                    string ingName, amtStr, priceStr;
                    getline(file, ingName);
                    getline(file, amtStr);
                    getline(file, priceStr);
                    
                    Ingredient temp(ingName, stod(amtStr), stod(priceStr));
                    foundRecipe.addIngredient(temp);
                }
                
                foundRecipe.show();
                file.close();
                return; 
            } else {
                for (int i = 0; i < numIngredients; i++) {
                    string skip;
                    getline(file, skip); 
                    getline(file, skip); 
                    getline(file, skip); 
                }
            }
        }
        
        cout << "Recipe '" << searchName << "' not found in " << filename << ".\n\n";
        file.close();
    }
};

int main() {
    Recipe meal("Chicken Bowl");

    Ingredient chicken("Chicken Breast (kg)", 0.35, 180.0);
    Ingredient eggs("Eggs (pcs)", 3.0, 6.5);
    Ingredient rice("White Rice (kg)", 0.1, 60.0);

    meal.addIngredient(chicken);
    meal.addIngredient(eggs);
    meal.addIngredient(rice);

    meal.show();

    string dbFile = "recipes.txt";
    meal.saveToFile(dbFile);

    Recipe::findRecipe(dbFile, "Chicken Bowl");
    
    Recipe::findRecipe(dbFile, "Apple Pie");

    return 0;
}