#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void line(int n=105, string ch=" *") {
    for(int i=0;i<n;i++) cout<<ch;
    cout<<endl<<endl;
}

void Theme(){
	cout<<endl<<endl;
    line();
    cout << setw(120) << "|| INVENTORY MANAGEMENT SYSTEM ||" <<endl<<endl;
    line();
}

void Role(){
    cout <<endl<<endl;
    cout << setw(108) << "Choice Role" << endl<<endl;
    cout << setw(100) << "1. ADMIN";
    cout << "\t 2. STAFF" << endl<<endl;
    cout << setw(103) << "3. SUPPLIER";
    cout << "\t 4. EXIT" << endl<<endl;
    line();
}

void staffRole(){
	system("cls");
	cout <<endl<<endl;
    cout << setw(108) << "Choice Role" << endl<<endl;
    cout << setw(100) << "1. Sales Manager";
    cout << "\t 2. Sales Person" << endl<<endl;
    cout << setw(91) << " 3. EXIT" << endl<<endl;
    line();
}

struct RequesrProductToSupplier{
	string requestId,productId,name,brand,category,model,price,variant,status,quantity,date;
};

class Admin {
	int price;
	unsigned int quantity,reOrderLevel,Flag;
	string productId,productName,category,brand,carModel,lastUpdateDate,variant,status;
public:
	//Admin Menus
    void menu();
    void productMenu();
    void stockMenu();
    void staffSupplierMenu(string);
    void reportMenu();
    
    //Product Management
    void addProduct(string, string, string, string, string, string, int, unsigned int, unsigned int, string, string, string);
    void editProduct(string,string);
    void deleteProduct(string,string);
    void viewProduct(string);
    
    //Stock Management
    void viewStock();
    void viewStockRequest(){ cout<<"[*] view stock request"<<endl; }
    void requestToSupplier(){ cout<<"Request to Supplier"<<endl; }
    
    //Supplier Management
    void addSupplier(unsigned int, string, string,string, string, string, string,string);
    void editSupplierDetails(unsigned int,string);
    void editSupplierCredential(unsigned int,string);
    void editSupplierStatus(unsigned int,string);
    void viewSupplier(string);
    
    //Reports
    void stockReport(){ cout<<"Stock Report"; }
    void supplierReport(){ cout<<"Supplier Report"; }
    void purchaseReport(){ cout<<"Purchase Report"; }
    
    //change Password
    void changePassword(){ cout<<"Change Password"; }
};

struct ProductDetails {
    string productId, productName, category, brand, carModel, variant, lastUpdateDate, status;
    int price;
    unsigned int quantity, reOrderLevel;
};

void Admin::menu(){
	system("cls");
    cout<<endl<<endl;
    cout << setw(110) << "|| ADMIN MENU ||" << endl;
    line();
    cout << setw(120) << "1. PRODUCT MANAGEMENT \t 2. STOCK MANAGEMENT" << endl<<endl;
    cout << setw(121) << "3. SUPPLIER MANAGEMENT \t 4. STAFF MANAGEMENT" << endl<<endl;
    cout << setw(109) << "5. REPORTS \t\t 6. CHANGE PASSWORD" << endl<<endl;
    cout << setw(86)  << "7. LOGOUT" << endl<<endl;
    line();
}

void Admin::productMenu(){
    cout<< endl<<endl;
    cout << setw(110) << " || PRODUCT MANAGEMENT || " << endl;
    cout<< endl;
    cout<< setw(110) <<"1. Add Product \t\t 2. Edit Product"<<endl<<endl;
    cout<< setw(113) <<"3. Delete Product \t\t 4. View Product"<<endl<<endl;
    cout<< setw(84) <<"5. Back"<<endl<<endl;
    line();
}

void Admin::addProduct(string getProductId,string getProductName,string getCategory,string getBrand,string getModel,string getVariant,
                       int getPrice,unsigned int getQuantity,unsigned int getReOrderLevel,string getLastUpdateDate,string getStatus,string role) {
    productId = getProductId;
    productName = getProductName;
    category = getCategory;
    brand = getBrand;
    carModel = getModel;
    variant = getVariant;
    price = getPrice;
    quantity = getQuantity;
    reOrderLevel = getReOrderLevel;
    lastUpdateDate = getLastUpdateDate;
    status = getStatus;
	
    if (role == "admin") {
        ofstream prodFile("products.txt", ios::app);
        prodFile << productId << ","<< productName << "," << category << "," << brand << "," << carModel << "," << variant << "," << price << ","
                 << quantity << "," << reOrderLevel << "," << lastUpdateDate << "," << status << endl;
        prodFile.close();
        
        ofstream stockFile("stock.txt", ios::app);
        stockFile << productId << "," << productName << "," << category << "," << brand << "," << carModel << "," << variant << "," << price << ","
                  << quantity << "," << 0 << "," << 0 << "," << status << endl;
        stockFile.close();
    } 
    else if (role == "supplier") {
    	ofstream suppFile("supplier_products.txt", ios::app);
        suppFile << productId << "," << productName << "," << category << "," << brand << "," << carModel << "," << variant << "," << price << "," << quantity << ","
                 << reOrderLevel << "," << lastUpdateDate << "," << status << endl;
        suppFile.close();
    }
}

void Admin::viewProduct(string role){
	cout<<endl<<endl;
	
	string filename,row,productId, productName, category, brand, model, variant, price, qty, reorder, lastUpdate, status;
	

	if (role == "admin" || role == "saler" || role == "manager") filename = "products.txt";
	else if (role == "supplier") filename = "supplier_products.txt";
    ifstream inFile(filename);
        
        cout << endl<< setw(110) <<"|| PRODUCT LIST ||" <<endl <<endl;
        cout << "ID\t\tName\t\t\tCategory\t\tBrand\t\tModel\t\t\tVariant\t\tPrice\t\tQty\t\tReOrder\t\tLastUpdate\tStatus\n";
        line(210,"-");
        
        bool checkProduct = false;
        while (getline(inFile, row)) {
        	if(role == "manager" || role == "saler"){
        		stringstream ss(row);
        	
	        	getline(ss, productId, ',');
		        getline(ss, productName, ',');
		        getline(ss, category, ',');
		        getline(ss, brand, ',');
		        getline(ss, model, ',');
		        getline(ss, variant, ',');
		        getline(ss, price, ',');
		        getline(ss, qty, ',');
		        getline(ss, reorder, ',');
		        getline(ss, lastUpdate, ',');
		        getline(ss, status, ',');
	            
	            if( status == "Active" ){
		        	cout << productId << "\t\t"
		             << productName << "\t\t" << category << "\t\t" << brand << "\t\t" << model << "\t\t" << variant << "\t\t"
		             << price << "\t\t" << qty << "\t\t" << reorder << "\t\t" << lastUpdate << "\t\t" << status << endl;
				}
				checkProduct = true;
	    	}else{
	    		for(char c : row){
	    			if (c == ',') cout << "\t\t"; 
					else cout << c;
				}
				cout<< endl;
				checkProduct = true;
			}
		}
		inFile.close();
		
		if(!checkProduct){
			cout<< endl << setw(120) << "|| Product not created or Supplied yet ||" <<endl<< endl;
		}
}

void Admin::editProduct(string getProductId,string role) {
    vector<ProductDetails> products;
    ProductDetails temp;
    string line,filename;
	
	if(role == "admin") filename = "products.txt"; 
	else if(role == "supplier") filename = "supplier_products.txt";
	ifstream inFile(filename);

    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;

        getline(ss, temp.productId, ',');
        getline(ss, temp.productName, ',');
        getline(ss, temp.category, ',');
        getline(ss, temp.brand, ',');
        getline(ss, temp.carModel, ',');
        getline(ss, temp.variant, ',');

        getline(ss, token, ',');
        temp.price = stoi(token);

        getline(ss, token, ',');
        temp.quantity = stoi(token);

        getline(ss, token, ',');
        temp.reOrderLevel = stoi(token);

        getline(ss, temp.lastUpdateDate, ',');
        getline(ss, temp.status);

        products.push_back(temp);
    }
    inFile.close();
    
    bool found = false;
    for (auto& product : products) {
        if (product.productId == getProductId) {
            found = true;
            cin.ignore();

            cout << "Enter New Product Name: ";
            getline(cin, product.productName);

            cout << "Enter New Category ( Engine, Transmission, Brakes, Electrical, Fuel System ) : ";
            getline(cin, product.category);

            cout << "Enter New Brand: ";
            getline(cin, product.brand);

            cout << "Enter New Car Model: ";
            getline(cin, product.carModel);

            cout << "Enter New Variant (e.g., Petrol/Diesel/EV): ";
            getline(cin, product.variant);

            cout << "Enter New Price: ";
            cin >> product.price;

            cout << "Enter New Quantity: ";
            cin >> product.quantity;

            cout << "Enter New Re-Order Level: ";
            cin >> product.reOrderLevel;
        
            product.status = (product.quantity < product.reOrderLevel) ? "Inactive" : "Active";
            product.lastUpdateDate = "NULL";

            cout << endl<< "Product updated Successfully"<< endl;
            break;
        }
    }
    if (!found) {
        cout << "? Product ID " << getProductId << " not found.\n";
        return;
    }
    
    if(role == "admin") filename = "products.txt";
	else if(role == "supplier") filename = "supplier_products.txt";
 	ofstream outFile(filename);
    for (const auto& product : products) {
        outFile << product.productId << "," << product.productName << "," << product.category << "," << product.brand << "," << product.carModel << ","
                << product.variant << "," << product.price << "," << product.quantity << "," << product.reOrderLevel << "," << product.lastUpdateDate << ","
                << product.status << endl;
    }
    outFile.close();
}

void Admin::deleteProduct(string productId, string role) {
    string filename;

    if (role == "admin")
        filename = "products.txt";
    else
        filename = "supplier_products.txt";

    ifstream inFile(filename);
    ofstream outFile("temp.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');

        if (id != productId)
            outFile << line << endl;
        else
            found = true;
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove(filename.c_str());                 // ? FIX
        rename("temp.txt", filename.c_str());     // ? FIX
    } else {
        remove("temp.txt");
        cout << "Product with ID " << productId << " not found in product file!" << endl;
    }

    ifstream stockIn("stock.txt");
    ofstream stockOut("stock_temp.txt");
    string stockLine;
    bool stockFound = false;

    while (getline(stockIn, stockLine)) {
        stringstream ss(stockLine);
        string id;
        getline(ss, id, ',');

        if (id != productId)
            stockOut << stockLine << endl;
        else
            stockFound = true;
    }

    stockIn.close();
    stockOut.close();

    remove("stock.txt");
    rename("stock_temp.txt", "stock.txt");

    if (found || stockFound)
        cout << "Product with ID " << productId
             << " deleted successfully from records." << endl;
}

void Admin::stockMenu(){
	cout<< endl;
    cout << setw(110) << "|| STOCK MANAGEMENT ||" << endl;
    cout<< endl;
    cout<< setw(91) <<"1. VIEW STOCK "<< setw(50) <<" 2. VIEW PRODUCT RESPONSE"<<endl<<endl;
    cout<< setw(109) <<"3. REQUEST SUPPLIER FOR PRODUCT "<< setw(16) <<" 4. BACK"<<endl<<endl;
    line();
}

void Admin::viewStock() {
    ifstream stockFile("stock.txt");
    string row;

    cout<< endl << endl << setw(110) << "|| STOCK REPORT || ";
	cout<< endl << endl << "ProdID\t\tName\t\tCategory\t\tBrand\t\tCarModel\tVariant\t\tPrice\t\tTotalQty\t\tQtyIn\t\tQtyOut\t\tStatus" << endl;
    line(210, "-");
	
	bool found = false;
    while (getline(stockFile, row)) {
        for (char c : row) {
            if (c == ',') cout << "\t\t";
            else cout << c;
            found = true;
        }
        cout << endl;
    }
	
	if(!found){
		cout << setw(120) << " || No Stock Outgoing or incoming Yet ||"<< endl<< endl;
	}
    stockFile.close();
}


void Admin::staffSupplierMenu(string role){
	cout<< endl;
	if (role == "supplier") role = "SUPPLIER";
	else if(role == "staff") role = "STAFF";
    cout << setw(96) << "|| " << role <<" MANAGEMENT ||" << endl;
    cout<< endl;
    cout<< setw(88) <<"1. Add new "<<role<< setw(25) <<" 2. Edit "<< role <<" Details"<<endl<<endl;
    cout<< setw(87) <<"3. Update "<< role <<" Credential "<< setw(31) <<"4. Active/Deactive Status"<<endl<<endl;
    cout<< setw(85) <<"5. View "<< role <<"\t\t\t 6. Exit"<<endl<<endl;
    line();
}

struct SupplierDetails {
    unsigned int supplierid;
    string supplierName;
    string contactno;
    string email;
    string Username;
    string password;
    string status;
};

void Admin::addSupplier(unsigned int getSupplierid, string getSupplierName, string getContactno,
                        string getEmail, string getUsername, string getPassword, string getStatus,string role) {
    SupplierDetails supplierDetail;
    supplierDetail.supplierid = getSupplierid;
    supplierDetail.supplierName = getSupplierName;
    supplierDetail.contactno = getContactno;
    supplierDetail.email = getEmail;
    supplierDetail.Username = getUsername;
    supplierDetail.password = getPassword;
    supplierDetail.status = getStatus;
	
    ofstream outFile;
    if(role == "supplier") outFile.open("suppliers.txt", ios::app); 
    else if(role == "staff") outFile.open("staff.txt", ios::app);

    outFile << supplierDetail.supplierid << "," << supplierDetail.supplierName << "," << supplierDetail.contactno << "," << supplierDetail.email << ","
            << supplierDetail.Username << "," << supplierDetail.password << "," << supplierDetail.status << endl;
    outFile.close();
}

void Admin::viewSupplier(string role){
	string filename;
	bool found = false;
	if (role == "staff") filename = "staff.txt";
    else if (role == "supplier") filename = "suppliers.txt";
        	
	ifstream inFile(filename);
	
	string row;
	cout<< endl << setw(96) << "|| "<< role <<" Details ||" << endl<< endl;
	cout << endl << "SupplierID\tSupplierName\tContact\t\t\tEmail\t\t\t\tUsername\t\tPassword\t\tStatus" <<endl;
	line(210,"-");
	while(getline(inFile,row)){
		for (char c : row) {
            if (c == ',') cout << "\t\t";
            else cout << c;
        }
        found = true;
        cout << endl;
	}
	inFile.close();
	
	if(!found) cout<< endl<< setw(90) << "|| "<<role<<" Not available Yet ||"<< endl<< endl;
}

void Admin::editSupplierDetails(unsigned int supplierid,string role) {

    vector<SupplierDetails> suppliers;
    SupplierDetails editDetails;
    string line,token,filename;

	if (role == "staff") filename = "staff.txt";
    else if (role == "supplier") filename = "suppliers.txt";
        	
	ifstream inFile(filename);

    while (getline(inFile, line)) {
        stringstream ss(line);

        getline(ss, token, ',');
        editDetails.supplierid = stoi(token);
        
        getline(ss, editDetails.supplierName, ',');
        getline(ss, editDetails.contactno, ',');
        getline(ss, editDetails.email, ',');
        getline(ss, editDetails.Username, ',');
        getline(ss, editDetails.password, ',');
        getline(ss, editDetails.status);

        suppliers.push_back(editDetails);
    }
    inFile.close();
    
    bool found = false;
    for (auto& supplier : suppliers) {
        if (supplier.supplierid == supplierid) {
        	found = true;
            cin.ignore();

            cout << "Enter New "<<role<<" Name: ";
            getline(cin, supplier.supplierName);

            cout << "Enter New Contact Number: ";
            cin >> supplier.contactno;
            cin.ignore();

            cout << "Enter New Email: ";
            getline(cin, supplier.email);

            cout << "\n "<< role << " details updated.\n";
            break;
        }
    }
    
    if (!found) {
        cout << "? Supplier ID " << supplierid << " not found.\n";
        return;
    }
	
	if (role == "staff") filename = "staff.txt";
    else if (role == "supplier") filename = "suppliers.txt";
        	
	ofstream outFile(filename);

    for (auto& supplier : suppliers) {
        outFile << supplier.supplierid << "," << supplier.supplierName << "," << supplier.contactno << "," << supplier.email << "," << supplier.Username << ","
                << supplier.password << "," << supplier.status << endl;
    }
    outFile.close();
}

void Admin::editSupplierCredential(unsigned int supplierid,string role) {

    vector<SupplierDetails> suppliers;
    SupplierDetails editDetails;
    string line,token,filename;
	
	if (role == "staff") filename = "staff.txt";
    else if (role == "supplier") filename = "suppliers.txt";
        	
	ifstream inFile(filename);
   
    while (getline(inFile, line)) {
        stringstream ss(line);

        getline(ss, token, ',');
        editDetails.supplierid = stoi(token);
        getline(ss, editDetails.supplierName, ',');
        getline(ss, editDetails.contactno, ',');
        getline(ss, editDetails.email, ',');
        getline(ss, editDetails.Username, ',');
        getline(ss, editDetails.password, ',');
        getline(ss, editDetails.status);

        suppliers.push_back(editDetails);
    }
    inFile.close();
    bool found = false;

    for (auto& supplier : suppliers) {
        if (supplier.supplierid == supplierid) {
            found = true;
            cin.ignore();
            cout << "Enter New Username: ";
            getline(cin, supplier.Username);

            cout << "Enter New Password: ";
            getline(cin, supplier.password);

            cout << "\n? Credentials updated.\n";
            break;
        }
    }
    if (!found) {
        cout << "? Supplier ID " << supplierid << " not found.\n";
        return;
    }
    
    if (role == "staff") filename = "staff.txt";
    else if (role == "supplier") filename = "suppliers.txt";
        	
	ofstream outFile(filename);
	
    for (const auto& supplier : suppliers) {
        outFile << supplier.supplierid << "," << supplier.supplierName << "," << supplier.contactno << "," << supplier.email << "," << supplier.Username << ","
                << supplier.password << "," << supplier.status << endl;
    }
    outFile.close();
}

void Admin::editSupplierStatus(unsigned int supplierid,string role) {
    vector<SupplierDetails> suppliers;
    SupplierDetails editDetails;
    string line,token,filename;

    if (role == "staff") filename = "staff.txt";
    else if (role == "supplier") filename = "suppliers.txt";
        	
	ifstream inFile(filename);

    while (getline(inFile, line)) {
        stringstream ss(line);

		getline(ss, token, ',');
        editDetails.supplierid = stoi(token);
        
        getline(ss, editDetails.supplierName, ',');
		getline(ss, editDetails.contactno, ',');
        getline(ss, editDetails.email, ',');
        getline(ss, editDetails.Username, ',');
        getline(ss, editDetails.password, ',');
        getline(ss, editDetails.status);

        suppliers.push_back(editDetails);
    }
    inFile.close();

    bool found = false;
    for (auto& supplier : suppliers) {
        if (supplier.supplierid == supplierid) {
            found = true;

            cin.ignore(); 
            cout << "Current Status: " << supplier.status << endl;
            cout << "Enter New Status (Active/Inactive): ";
            getline(cin, supplier.status);
            cout << "\n? Status updated.\n";
            break;
        }
    }
    if (!found) {
        cout << "? Supplier ID " << supplierid << " not found.\n";
        return;
    }

    if (role == "staff") filename = "staff.txt";
    else if (role == "supplier") filename = "suppliers.txt";
        	
	ofstream outFile(filename);
	
    for (const auto& supplier : suppliers) {
        outFile << supplier.supplierid << "," << supplier.supplierName << "," << supplier.contactno << "," << supplier.email << "," << supplier.Username << ","
                << supplier.password << "," << supplier.status << endl;
    }
    outFile.close();
}

void Admin::reportMenu(){
	cout<< endl;
    cout << setw(107) << "Reports" << endl;
    cout<< endl;
    cout<< setw(93) <<"1. Stock Report"<< setw(35) <<"2. Supplier Report"<<endl<<endl;
    cout<< setw(96) <<"3. Purchase Report"<< setw(21) <<"4. Back"<<endl<<endl;
    line();
}

class Staff{
	string requestId,productId,date,status;
	unsigned int sellquantity;
	string basePath;
public:
	
	//Staff Menus
    void SalesManagerMenu();
    void SalesPersonMenu();
    
    //Sales Manager Menu
    void salesRequest();
    void viewSalesReport();
    void requestSupplier(string,unsigned int);
    void viewSupplierProduct();
    void changePassword(){ cout<<"Change password"; }
    
    //Sales Person Menu
    bool saleProduct(string, string, unsigned int, string, string);
    void viewStatusOfSellingProduct();
};

void Staff::SalesManagerMenu(){
    cout<<endl<<endl;
    cout << setw(110) << "|| SALES MANAGER MENU ||" << endl;
    line();
    cout << setw(90) << "1. VIEW PRODUCT " << setw(30) <<" 2. SALES REQUEST" << endl<<endl;
    cout << setw(95) << "3. VIEW SALES REPORT " << setw(28) <<" 4. REQUEST SUPPLIER" << endl<<endl;
    cout << setw(104) << "5. RESPONSE OF SUPPLIER PRODUCT " << setw(19) <<" 6. CHANGE PASSWORD " << endl<<endl;
    cout << setw(84) << "7. LOGOUT "<< endl<< endl;
    line();
}

struct Product {
    string id, name, category, brand, carModel, variant, price, status , lastUpdateDate, reorder, quantity;
    unsigned int sell;
};

struct SalesReq {
    string reqId, prodId, date, status;
    unsigned int qty;
};

void Staff::salesRequest() {
    string sellProductId,row,sellstr;
    bool found = false,availableRequest = false;
    int ch;
    
    ifstream salesFile("sales_request.txt");
    ifstream productFile("products.txt");

	vector<Product> products;
    
    while (getline(productFile, row)) {
        stringstream ss(row);
        Product p;
        string dummy;

        getline(ss, p.id, ',');
        getline(ss, p.name, ',');
        getline(ss, p.category, ',');
        getline(ss, p.brand, ',');
        getline(ss, p.carModel, ',');
        getline(ss, p.variant, ',');
        getline(ss, p.price, ',');
        getline(ss, sellstr, ',');
        p.sell = stoi(sellstr);
        getline(ss, p.reorder, ',');   
        getline(ss, p.lastUpdateDate, ',');
        getline(ss, p.status, ','); 
        products.push_back(p);
    }
    productFile.close(); 

    cout << endl<<"ReqID\t\tProdID\t\tName\t\tCategory\t\tBrand\t\tCarModel\tPrice\t\tSell\t\tVariant\t\tQuantity\t\tStatus\t\tDate" << endl;
    line(210,"-");
	
	
    vector<SalesReq> requests;

    while (getline(salesFile, row)) {
        stringstream ss(row);
        SalesReq r;
        string dummy;

        getline(ss, r.reqId, ',');
        getline(ss, r.prodId, ',');
        getline(ss, dummy, ',');
        r.qty = stoi(dummy);
        getline(ss, r.date, ',');
        getline(ss, r.status, ',');
        requests.push_back(r);
		
		if (r.status == "Rejected" || r.status == "Approved") {
	        continue;
	    }
        for (auto &p : products) {
            if (p.id == r.prodId) {
	            cout << r.reqId << "\t\t" << r.prodId << "\t\t" << p.name << "\t\t" << p.category << "\t\t" << p.brand << "\t\t" 
				<< p.carModel << "\t\t" << p.price << "\t\t" << p.sell << "\t\t" << p.variant << "\t\t" << r.qty << "\t\t" 
				<< r.status << "\t\t" << r.date << endl;
				availableRequest = true;
            }
        }
    }
    salesFile.close();
    
    if (!availableRequest) {
	    cout << " No sales requests found." << endl;
	    return;
	}

    cout << endl <<"Enter Product Id which you want to sell: ";
    cin >> sellProductId;

    for (auto &r : requests) {
        if (r.prodId == sellProductId) {
            for (auto &p : products) {
            	if(r.prodId == p.id && (r.status == "Pending" || r.status == "Requesting")){
	                cout << endl << "=== Product Sale Details ===" << endl;
	                cout << "Product ID : " << p.id << endl;
	                cout << "Name       : " << p.name << endl;
	                cout << "Category   : " << p.category << endl;
	                cout << "Brand      : " << p.brand << endl;
	                cout << "Car Model  : " << p.carModel << endl;
	                cout << "Variant    : " << p.variant << endl;
	                cout << "Price      : " << p.price << endl;
	                cout << "Quantity      : " << p.sell << endl;
	                cout << "Requestrd Quantity   : " << r.qty << endl;
	                cout << "Date       : " << r.date << endl;
	                cout << "Status     : " << r.status << endl;
	                
	                time_t now = time(0);
				    tm *ltm = localtime(&now);
				    char dateStr[20];
				    sprintf(dateStr, "%04d-%02d-%02d", 
				            1900 + ltm->tm_year, 
				            1 + ltm->tm_mon, 
				            ltm->tm_mday);
				            
	                if (r.qty > p.sell) {
	                	cout<< endl<<"No Enough stock !! " <<endl;
					    cout << "1. REJECT " << endl;
					    cout << "2. REQUEST TO SUPPLIER. " << endl<<endl;
					    cout << "Enter Your choice : ";
					    cin >> ch;
					    if(ch == 1){
					    	r.status = "Rejected";
						    ofstream outSales("sales_request.txt");
						    for (auto &r : requests) {
						        outSales << r.reqId << "," << r.prodId << "," << r.qty << ","
						                 << r.date << "," << r.status << endl;
						    }
						    outSales.close();
						}else if(ch == 2){
							bool duplicate = false;
							ifstream requestFile("request_to_suppler.txt",ios::app);
							while (getline(requestFile, row)) {
							    stringstream ss(row);
							    string reqId, prodId, name, brand, category, model, price, variant, qty, date, status;
							
							    getline(ss, reqId, ',');
							    getline(ss, prodId, ',');
							    getline(ss, name, ',');
							    getline(ss, brand, ',');
							    getline(ss, category, ',');
							    getline(ss, model, ',');
							    getline(ss, price, ',');
							    getline(ss, variant, ',');
							    getline(ss, qty, ',');
							    getline(ss, date, ',');
							    getline(ss, status, ',');
							
							    if (reqId == r.reqId && prodId == p.id && stoi(qty) == r.qty && status == "Requesting") {
							        duplicate = true;
							        break;
							    }
							}
							requestFile.close();
							
							if (duplicate) {
							    cout << endl<< "This request is already made to Supplier!"<< endl;
							} else {
							    ofstream requestToSuppler("request_to_suppler.txt",ios::app);
							    string status = "Requesting";
							    requestToSuppler << r.reqId << "," << p.id << "," << p.name << "," << p.brand << "," << p.category << "," << p.carModel << "," 
							                     << p.price << "," << p.variant << "," << r.qty << "," << dateStr << "," << status << endl;
							    requestToSuppler.close();
							
							    r.status = "Requesting";
							    ofstream outSales("sales_request.txt");
							    for (auto &r : requests) {
							        outSales << r.reqId << "," << r.prodId << "," << r.qty << "," << r.date << "," << r.status << endl;
							    }
							    outSales.close();
							    cout << "\n? Product requested to Supplier successfully.\n";
							}
						}else{
							cout<< endl<< endl<<"Wrong choice !!!"<<endl<< endl;
							return;
						}
					} else {
					    cout << "SALES CAN BE APPROVED." << endl;
					    p.sell = p.sell - r.qty;
						
					    ofstream outFile("products.txt");
					    for (auto &p : products){
					    	if (p.id == r.prodId) p.lastUpdateDate = dateStr;
					        else p.lastUpdateDate = p.lastUpdateDate;
					        
					        outFile << p.id << "," << p.name << "," << p.category << "," << p.brand << "," << p.carModel 
									<< "," << p.variant << "," << p.price << "," << p.sell << "," << p.reorder << ","  << p.lastUpdateDate 
									<< "," << p.status << endl;
					    }
					    outFile.close();
					    
						ifstream stockIn("stock.txt");
						vector<string> stockLines;
						string line;
						
						while (getline(stockIn, line)) {
						    stockLines.push_back(line);
						}
						stockIn.close();
						ofstream stockOut("stock.txt");
						for (string &line : stockLines) {
						    stringstream ss(line);
						    string id, name, category, brand, carModel, variant, price, qty, reorder, qtyOut, status;
						
						    getline(ss, id, ',');
						    getline(ss, name, ',');
						    getline(ss, category, ',');
						    getline(ss, brand, ',');
						    getline(ss, carModel, ',');
						    getline(ss, variant, ',');
						    getline(ss, price, ',');
						    getline(ss, qty, ',');
						    getline(ss, reorder, ',');
						    getline(ss, qtyOut, ',');
						    getline(ss, status, ',');
						
						    if (id == r.prodId) {
						        int qOut = stoi(qtyOut);
						        int quantityStock = stoi(qty);
						        qOut += r.qty;             
						        quantityStock -= r.qty;    
						        qtyOut = to_string(qOut);
						        qty = to_string(quantityStock);
						    }
						
						    stockOut << id << "," << name << "," << category << "," << brand << "," << carModel << ","
						             << variant << "," << price << "," << qty << "," << reorder << "," << qtyOut << "," << status << endl;
						}
						stockOut.close();
					    
					    r.status = "Approved";
					    //UPDATE IN SALES_REQUEST FILE
					    ofstream outSales("sales_request.txt");
					    for (auto &r : requests) {
					        outSales << r.reqId << "," << r.prodId << "," << r.qty << "," << r.date << "," << r.status << endl;
					    }
					    outSales.close();
					    
					    //Create sales
					    ofstream salesOut("sales.txt",ios::app);
					    srand(time(0));
					    int uniqueNum = 1000 + rand() % 9000;
					    string transactionId = "T" + to_string(uniqueNum);
					    salesOut << transactionId << "," << p.id << "," << p.name << "," << p.brand << "," << p.category << "," << p.carModel << "," << p.price << "," 
				             << p.variant << "," << r.qty << "," << dateStr << "," << endl;
				    	salesOut.close();
					}
        		}
                found = true;
            }
        }
    }

    if (!found) cout << "? No sales request found for Product ID " << sellProductId << endl;
}

void Staff::requestSupplier(string getProductId, unsigned int getQuantity) {
    string row, getRequestId;
    int currentId;
    bool found = false, duplicate = false;

    ifstream productFile("products.txt");
    ifstream checkFile("request_to_suppler.txt");

    time_t now = time(0);
    tm *ltm = localtime(&now);
    char dateStr[20];
    sprintf(dateStr, "%04d-%02d-%02d",
            1900 + ltm->tm_year,
            1 + ltm->tm_mon,
            ltm->tm_mday);

    srand(time(0));
    currentId = rand() % 1001;
    stringstream rss;
    rss << setw(4) << setfill('0') << currentId;
    getRequestId = "R" + rss.str();

    while (getline(checkFile, row)) {
        stringstream ss(row);
        string reqId, prodId, name, brand, category, model, price, variant, qty, date, status;

        getline(ss, reqId, ',');
        getline(ss, prodId, ',');
        getline(ss, name, ',');
        getline(ss, brand, ',');
        getline(ss, category, ',');
        getline(ss, model, ',');
        getline(ss, price, ',');
        getline(ss, variant, ',');
        getline(ss, qty, ',');
        getline(ss, date, ',');
        getline(ss, status, ',');

        if (prodId == getProductId && stoi(qty) == getQuantity && status == "Requesting") {
            duplicate = true;
            break;
        }
    }
    checkFile.close();

    if (duplicate) {
        cout << "?? This product request already exists with same quantity!" << endl;
        return;
    }
    
    while (getline(productFile, row)) {
        stringstream ss(row);
        string id, name, category, brand, model, variant, price, qty, reorder, lastUpdate;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, category, ',');
        getline(ss, brand, ',');
        getline(ss, model, ',');
        getline(ss, variant, ',');
        getline(ss, price, ',');
        getline(ss, qty, ',');
        getline(ss, reorder, ',');
        getline(ss, lastUpdate, ',');

        if (id == getProductId) {
            found = true;

            ofstream requestFile("request_to_suppler.txt", ios::app);

            requestFile << getRequestId << "," << id << "," << name << "," << brand << "," << category << "," << model << "," << price << ","
                        << variant << "," << getQuantity << "," << dateStr << "," << "Requesting" << endl;
            requestFile.close();
            cout << "? Product request sent to supplier successfully." << endl;
            break;
        }
    }

    if (!found) cout << "? Product ID " << getProductId << " not found in stock!" << endl;
    productFile.close();
}

void Staff::viewSupplierProduct() {
    ifstream responseFile("request_to_suppler.txt");
    string row, getRequestId;
    bool found = false;

    cout << endl << setw(120) << "|| PRODUCT LIST WHICH IS SUPPLY BY THE SUPPLIER ||" << endl << endl;
    cout << "RequestId\t\tProductId\tName\t\tBrand\t\tCategory\t\tModel\t\tPrice\t\tVariant\t\tQuantity\t\tDate\t\tStatus" << endl;
    line(210, "-");

    vector<string> requests;
    while (getline(responseFile, row)) {
        requests.push_back(row);
        for (char ch : row) {
            if (ch == ',') cout << "\t\t";
            else cout << ch;
        }
        cout << endl;
        found = true;
    }
    responseFile.close();

    if (!found) {
        cout << endl << "Supplier Response is Not created yet" << endl << endl;
        return;
    }

    cout << "Enter Request id which quantity add in your stock : ";
    cin >> getRequestId;

    string matchedLine = "";
    for (string &reqLine : requests) {
        stringstream ss(reqLine);
        string reqId;
        getline(ss, reqId, ',');
        if (reqId == getRequestId) {
            matchedLine = reqLine;
            break;
        }
    }

    if (matchedLine == "") {
        cout << "? Request ID " << getRequestId << " not found!" << endl;
        return;
    }

    stringstream ss(matchedLine);
    string requestId, prodId, name, brand, category, model, price, variant, qtyStr, date, status;
    getline(ss, requestId, ',');
    getline(ss, prodId, ',');
    getline(ss, name, ',');
    getline(ss, brand, ',');
    getline(ss, category, ',');
    getline(ss, model, ',');
    getline(ss, price, ',');
    getline(ss, variant, ',');
    getline(ss, qtyStr, ',');
    getline(ss, date, ',');
    getline(ss, status, ',');

    if (status == "Requesting") {
        cout << "? Waiting for supplier to respond. Try again later!" << endl;
        return;
    } else if (status == "Reject") {
        cout << "? Supplier has no stock for this product (Request Rejected)." << endl;
        return;
    } else if (status == "Delivered") {
	    cout << "? Stock for this request is already added previously!" << endl;
	    return;
	}


    int suppliedQty = stoi(qtyStr);

    time_t now = time(0);
    tm *ltm = localtime(&now);
    char dateStr[20];
    sprintf(dateStr, "%04d-%02d-%02d",
            1900 + ltm->tm_year,
            1 + ltm->tm_mon,
            ltm->tm_mday);

    ifstream inProd("products.txt");
    vector<string> prodLines;
    while (getline(inProd, row)) prodLines.push_back(row);
    inProd.close();

    ofstream outProd("products.txt");
    for (string &line : prodLines) {
        stringstream ss(line);
        string id, pname, pcategory, pbrand, pmodel, pvariant, pprice, pqty, reorder, lastUpdate, pstatus;

        getline(ss, id, ',');
        getline(ss, pname, ',');
        getline(ss, pcategory, ',');
        getline(ss, pbrand, ',');
        getline(ss, pmodel, ',');
        getline(ss, pvariant, ',');
        getline(ss, pprice, ',');
        getline(ss, pqty, ',');
        getline(ss, reorder, ',');
        getline(ss, lastUpdate, ',');
        getline(ss, pstatus, ',');

        if (id == prodId) {
            int newQty = stoi(pqty) + suppliedQty;
            pqty = to_string(newQty);
            lastUpdate = dateStr;
        }

        outProd << id << "," << pname << "," << pcategory << "," << pbrand << "," << pmodel << ","
                << pvariant << "," << pprice << "," << pqty << "," << reorder << "," << lastUpdate << "," << pstatus << endl;
    }
    outProd.close();

    ifstream inStock("stock.txt");
    vector<string> stockLines;
    while (getline(inStock, row)) stockLines.push_back(row);
    inStock.close();

    ofstream outStock("stock.txt");
    for (string &line : stockLines) {
        stringstream ss(line);
        string id, pname, pcategory, pbrand, pmodel, pvariant, pprice, pqty, qtyIn, qtyOut, pstatus;

        getline(ss, id, ',');
        getline(ss, pname, ',');
        getline(ss, pcategory, ',');
        getline(ss, pbrand, ',');
        getline(ss, pmodel, ',');
        getline(ss, pvariant, ',');
        getline(ss, pprice, ',');
        getline(ss, pqty, ',');
        getline(ss, qtyIn, ',');
        getline(ss, qtyOut, ',');
        getline(ss, pstatus, ',');

        if (id == prodId) {
            int newQty = stoi(pqty) + suppliedQty;
            pqty = to_string(newQty);

            int inVal = qtyIn.empty() ? 0 : stoi(qtyIn);
            inVal += suppliedQty;
            qtyIn = to_string(inVal);
        }

        outStock << id << "," << pname << "," << pcategory << "," << pbrand << "," << pmodel << ","
                 << pvariant << "," << pprice << "," << pqty << "," << qtyIn << "," << qtyOut << "," << pstatus << endl;
    }
    outStock.close();

    ifstream inReq("request_to_suppler.txt");
	vector<string> reqLines;
	while (getline(inReq, row)) reqLines.push_back(row);
	inReq.close();
	
	ofstream outReq("request_to_suppler.txt");
	for (string &line : reqLines) {
	    stringstream ss(line);
	    string reqId, prodIdFile, name, brand, category, model, price, variant, qty, date, status;
	
	    getline(ss, reqId, ',');
	    getline(ss, prodIdFile, ',');
	    getline(ss, name, ',');
	    getline(ss, brand, ',');
	    getline(ss, category, ',');
	    getline(ss, model, ',');
	    getline(ss, price, ',');
	    getline(ss, variant, ',');
	    getline(ss, qty, ',');
	    getline(ss, date, ',');
	    getline(ss, status, ',');
	
	    if (prodIdFile == prodId && status == "Supplied") {
	        status = "Delivered";
	    }
	
	    outReq << reqId << "," << prodIdFile << "," << name << "," << brand << "," << category << "," << model << ","
	           << price << "," << variant << "," << qty << "," << date << "," << status << endl;
	}
	outReq.close();
	
	cout << "\n Stock added Successfully. \n";
}

void Staff::viewSalesReport(){
	ifstream inFile("sales.txt");
    string row;
    bool checkProduct = false;
	
	cout<< endl << endl << setw(110) << "|| SALES REPORT || ";
	cout<< endl << endl << "Transaction Id\tProduct ID\t\tName\t\tBrand\t\tCayegory\tcar Model\t\tPrice\t\tVariant\tQuantity\ttDate"<< endl;
	line(210,"-");
    while (getline(inFile, row)) {
        for (char c : row) {
            if (c == ',') 
                cout << "\t\t"; 
            else 
                cout << c;
        }
        cout << endl<<endl;
        checkProduct = true;
    }

    if (!checkProduct) cout << setw(115) << " || No sales data available ||" << endl;
    inFile.close();
}

void Staff::SalesPersonMenu(){
	cout<<endl<<endl;
    cout << setw(110) << "|| SALES PERSON MENU ||" << endl;
    line();
    cout << setw(90) << "1. VIEW PRODUCT " << setw(37) <<" 2. SELL PRODUCT" << endl<<endl;
    cout << setw(108) << "3. VIEW STATUS OF SELLING PRODUCT " << setw(25) <<" 4. CHANGE PASSWORD " << endl<<endl;
    cout << setw(84) << "5. LOGOUT " <<endl<<endl;
    line();
}

bool Staff::saleProduct(string getRequestId, string getProductId, unsigned int getSellQuantity, string getDate, string getStatus){
	bool found=false;
	
	requestId = getRequestId;
	productId = getProductId;
	sellquantity = getSellQuantity;
	date = getDate;
	status = getStatus;
	
	ifstream inFile("products.txt");
	string row;
	while (getline(inFile, row)) {
        stringstream ss(row);
        string id;
        getline(ss, id, ',');

        if (id == getProductId) {
            ofstream outFile("sales_request.txt",ios::app);
	
			outFile << requestId << "," << productId << "," << sellquantity << "," << date << "," << status << endl;
			outFile.close();
			found = true;
        }
    }
    return found;
}

void Staff::viewStatusOfSellingProduct(){
	ifstream inFile("sales_request.txt");
	string row;
	bool found = false;
        cout << endl<< "Request ID\tProduct ID\tQuantity\tDate\t\t\tstatus \n";
        line(210,"-");
        while (getline(inFile, row)) {
            for (char c : row) {
                if (c == ',') cout << "\t\t";
                else cout << c;
            }
            found = true;
            cout << endl;
        }
        
        if(!found) cout<< "Request Not Created Yet."; 
        inFile.close();
}

class Supplier{
	string basePath;
public:
	
	//Supplier Menus
    void menu();
    
    void stockRequest();
    void supplyProduct(string);
    void productHistory();
    void changePassword(){ cout<<"Change Password"; }
};

void Supplier::menu(){
	cout<<endl<<endl;
    cout << setw(110) << "|| SUPPLIER MENU ||" << endl;
    line();
    cout << setw(98) << "1. VIEW STOCK REQUEST"<< setw(37) <<"2. SUPPLY PRODUCT TO STORE" << endl<<endl;
    cout << setw(100) << "3. VIEW SUPPLY HISTORY "<< setw(28) <<"4.  CHANGE PASSWORD" << endl<<endl;
    cout << setw(98) << "5. PRODUCT MANAGEMENT" << setw(20) << "6. LOGOUT" << endl<<endl;
    line();
}

void Supplier::stockRequest() {
	bool found = false;
    ifstream RequestOfProducts("request_to_suppler.txt");
    string row;
    cout << endl << setw(125) << " || Requesting Stock from the Car Inventory System || ";
    cout << endl << endl << "RequestID\t\tProductID\tName\t\tBrand\t\tCategory\tCar Model\t\tPrice\t\tVariant\t\tQuantity\t\tDate\tStatus" << endl;
    line(210, "-");

    while (getline(RequestOfProducts, row)) {
        stringstream ss(row);
        string requestId, productId, name, brand, category, model, variant, price, qty, date, status;

        getline(ss, requestId, ',');
        getline(ss, productId, ',');
        getline(ss, name, ',');
        getline(ss, brand, ',');
        getline(ss, category, ',');
        getline(ss, model, ',');
        getline(ss, variant, ',');
        getline(ss, price, ',');
        getline(ss, qty, ',');
        getline(ss, date, ',');
        getline(ss, status, ',');

        if (status == "Requesting") {
            for (char ch : row) {
                if (ch == ',') cout << "\t\t";
                else cout << ch;
            }
            found = true;
            cout << endl;
        }
    }
    
    if(!found) cout<< endl << setw(120) << "|| NO REQUEST IS CREATED YET ||" <<endl << endl;
}

void Supplier::supplyProduct(string getRequestId) {
    vector<string> requestLines;
    string line;
    bool found = false, matched = false, sufficientQty = false;

    ifstream requestFile("request_to_suppler.txt");
    while (getline(requestFile, line)) requestLines.push_back(line);
    requestFile.close();

    for (string &reqLine : requestLines) {
        stringstream ss(reqLine);
        string requestId, productId, name, brand, category, model, variant, price, qty, date, status;

        getline(ss, requestId, ',');
        getline(ss, productId, ',');
        getline(ss, name, ',');
        getline(ss, brand, ',');
        getline(ss, category, ',');
        getline(ss, model, ',');
        getline(ss, price, ',');
        getline(ss, variant, ',');
        getline(ss, qty, ',');
        getline(ss, date, ',');
        getline(ss, status, ',');

        if (requestId == getRequestId && status == "Requesting") {
            ifstream supplierFile("supplier_products.txt");
            string suppLine;
            while (getline(supplierFile, suppLine)) {
                stringstream sss(suppLine);
                string spId, spName, spCategory, spBrand, spModel, spVariant, spPrice, spQty, spReorder, spLastUpdate, spStatus;

                getline(sss, spId, ',');
                getline(sss, spName, ',');
                getline(sss, spCategory, ',');
                getline(sss, spBrand, ',');
                getline(sss, spModel, ',');
                getline(sss, spVariant, ',');
                getline(sss, spPrice, ',');
                getline(sss, spQty, ',');
                getline(sss, spReorder, ',');
                getline(sss, spLastUpdate, ',');
                getline(sss, spStatus);

                if (spName == name && spBrand == brand &&
                    spCategory == category && spModel == model && spVariant == variant) {

                    matched = true;
                    unsigned int supplierQty = stoi(spQty);
                    unsigned int requestQty = stoi(qty);

                    if (supplierQty >= requestQty) {
					    reqLine = requestId + "," + productId + "," + name + "," + brand + "," + category + "," + model + "," + price + "," + variant + "," + qty + "," + date + ",Supplied";
					    sufficientQty = true;
					
					    vector<string> supplierLines;
					    ifstream supplierIn("supplier_products.txt");
					    string sLine;
					    while (getline(supplierIn, sLine)) {
					        stringstream sss(sLine);
					        string spId, spName, spCategory, spBrand, spModel, spVariant, spPrice, spQty, spReorder, spLastUpdate, spStatus;
					        getline(sss, spId, ',');
					        getline(sss, spName, ',');
					        getline(sss, spCategory, ',');
					        getline(sss, spBrand, ',');
					        getline(sss, spModel, ',');
					        getline(sss, spVariant, ',');
					        getline(sss, spPrice, ',');
					        getline(sss, spQty, ',');
					        getline(sss, spReorder, ',');
					        getline(sss, spLastUpdate, ',');
					        getline(sss, spStatus);
					
					        if (spName == name && spBrand == brand &&
					            spCategory == category && spModel == model && spVariant == variant) {
					            unsigned int newQty = stoi(spQty) - requestQty;
					            sLine = spId + "," + spName + "," + spCategory + "," + spBrand + "," + spModel + "," +
					                    spVariant + "," + spPrice + "," + to_string(newQty) + "," + spReorder + "," +
					                    spLastUpdate + "," + spStatus;
					        }
					        supplierLines.push_back(sLine);
					    }
					    supplierIn.close();
			
					    ofstream supplierOut("supplier_products.txt");
					    for (auto &sl : supplierLines) {
					        supplierOut << sl << endl;
					    }
					    supplierOut.close();
					}
                    break;
                }
            }
            supplierFile.close();

            if (!matched || !sufficientQty) {
			    reqLine = requestId + "," + productId + "," + name + "," + brand + "," + category + "," + model + "," + price + "," + variant + "," + qty + "," + date + ",Rejected";
			
			    vector<string> salesLines;
			    ifstream salesIn("sales_request.txt");
			    string sLine;
			    while (getline(salesIn, sLine)) {
			        stringstream ss(sLine);
			        string srId, spId, sQty, sDate, sStatus;
			        getline(ss, srId, ',');
			        getline(ss, spId, ',');
			        getline(ss, sQty, ',');
			        getline(ss, sDate, ',');
			        getline(ss, sStatus, ',');
			
			        if (srId == requestId && spId == productId && sQty == qty) sLine = srId + "," + spId + "," + sQty + "," + sDate + ",Rejected";
			        salesLines.push_back(sLine);
			    }
			    salesIn.close();
			
			    ofstream salesOut("sales_request.txt");
			    for (auto &sl : salesLines) salesOut << sl << endl;
			    salesOut.close();
			}

            found = true;
            break;
        }
    }

    ofstream outFile("request_to_suppler.txt");
    for (auto &r : requestLines) outFile << r << endl;
    outFile.close();

    if (found) {
        if (!matched) cout << "? Product is currently not available for supply." << endl;
        else {
            if (!sufficientQty) cout << "?? Stock is not enough to supply." << endl;
            else cout << "? Product supplied successfully." << endl;
        }
    }
    else cout << "? Request ID not found." << endl;
}

void Supplier::productHistory(){
    bool found = false;
    ifstream RequestOfProducts("request_to_suppler.txt");
    string row;
    cout << endl << setw(115) << " || Supplied Product list || ";
    cout << endl << endl 
         << "RequestID\t\tProductID\tName\t\tBrand\t\tCategory\tCar Model\t\tPrice\t\tVariant\t\tQuantity\t\tDate\tStatus" 
         << endl;
    line(210, "-");

    while (getline(RequestOfProducts, row)) {
        stringstream ss(row);
        string requestId, productId, name, brand, category, model, price, variant, qty, date, status;

        getline(ss, requestId, ',');
        getline(ss, productId, ',');
        getline(ss, name, ',');
        getline(ss, brand, ',');
        getline(ss, category, ',');
        getline(ss, model, ',');
        getline(ss, price, ',');     
        getline(ss, variant, ','); 
        getline(ss, qty, ',');
        getline(ss, date, ',');
        getline(ss, status, ',');

        if (status == "Supplied" || status == "Delivered") {
            for (char ch : row) {
                if (ch == ',') cout << "\t\t";
                else cout << ch;
            }
            found = true;
            cout << endl;
        }
    }
    
    if(!found) cout<< endl << setw(115) << "|| NO REQUEST IS CREATED YET ||" <<endl << endl;
}

bool login(string username, string password) {
    string getUsername, getPassword;
    int attempts = 1;
    char ch;

    while (attempts < 4) {
    	cout<<endl;
    	getUsername.clear();
        getPassword.clear();
        cout << "Enter username: ";
        cin >> getUsername;
        cout << "Enter password: ";
        while ((ch = getch()) != 13) {
	        getPassword.push_back(ch);
	        cout << "*";
	    }
	
        if (getUsername == username && getPassword == password) {
            cout << endl <<  "Login Successful!"<<endl;
            return true;
        } else {
            cout << endl <<  "? Invalid credentials!"<<endl<<endl;
            attempts++;
        }
    }

    cout << "?? Too many failed attempts! Please wait 30 seconds...\n";
    this_thread::sleep_for(chrono::seconds(30));
    return false;
}

int main(){
    Admin admin;
    Staff staff;
    Supplier supplier;
    int choiceRole,choiceMenuItem,choiceOperation,choicestaffRole,getPrice,autoId=1000,currentId;
    bool loginStatus;
	unsigned int getQuantity,getReOrderLevel,getSellQuantity,getSupplierid;
	string getRequestId,getProductId,getProductName,getCategory,getBrand,getModel,getLastUpdateDate,getVariant,getStatus,
		   getDate,getSupplierName,getStaffName,getUsername,getPassword,getEmail,getContactno;
   
    Theme();
    do{
        Role();
        cout<<"Enter Your choice (1-4): ";
        cin>>choiceRole;

        if(choiceRole == 1){
        	loginStatus = login("ADMIN","admin@123");
        	if(loginStatus){
        		do{
	                admin.menu();
	                cout<<"Select the management you want : ";
	                cin>>choiceMenuItem;
	                
	                if(choiceMenuItem == 1){
	                    do{
	                        admin.productMenu();
	                        cout<<"Select operation you want : ";
	                        cin>>choiceOperation;
	                        
	                        if(choiceOperation == 1) { 
	                        	srand(time(0));
							    int uniqueNum = 1000 + rand() % 9000;
							    getProductId = "P" + to_string(uniqueNum);
								
								cin.ignore();
							    cout << "Enter Product name: ";
							    getline(cin, getProductName);
							
							    cout << "Enter Category ( Engine, Transmission, Brakes, Electrical, Fuel System ) : ";
							    getline(cin, getCategory);
							
							    cout << "Enter Brand: ";
							    getline(cin, getBrand);
							
							    cout << "Enter Car Model: ";
							    getline(cin, getModel);
							
							    cout << "Enter Variant (e.g., Petrol/Diesel/EV): ";
							    getline(cin, getVariant);
							
							    cout << "Enter Price (in Rs): ";
							    cin >> getPrice;
							
							    cout << "Enter Quantity in stock: ";
							    cin >> getQuantity;
							
							    cout << "Enter Re-Order Level: ";
							    cin >> getReOrderLevel;
							
							    getLastUpdateDate = "NULL";
							
							    if ( getQuantity < getReOrderLevel ){
							    	getStatus = "Inactive";
								}else{
									getStatus = "Active";
								}
								
								admin.addProduct(getProductId,getProductName,getCategory,getBrand,getModel,getVariant,getPrice,getQuantity,
								getReOrderLevel,getLastUpdateDate,getStatus,"admin"); 
							}
	                        else if(choiceOperation == 2) {
								admin.viewProduct("admin");
								
							    cout << endl<<"Enter the product Id which you want to Edit : ";
							    cin >> getProductId;
							    
								admin.editProduct(getProductId,"admin"); 
							} 
	                        else if(choiceOperation == 3) {
	                        	admin.viewProduct("admin");
							    cout << endl<<"Enter the product Id which you want to delete : ";
							    cin >> getProductId;
							    admin.deleteProduct(getProductId,"admin");
							}
	                        else if(choiceOperation == 4) { admin.viewProduct("admin"); }
	                    }while(choiceOperation != 5);
	                }else if(choiceMenuItem == 2){
	                    do{
	                        admin.stockMenu();
	                        cout<<"Select operation you want : ";
	                        cin>>choiceOperation;
	                        
	                        if(choiceOperation == 1) { admin.viewStock(); }
	                        else if(choiceOperation == 2) { staff.viewSupplierProduct(); }
	                        else if(choiceOperation == 3) { 
								admin.viewProduct("admin");
	    						
	    						cout << endl<<"Enter Product Id : ";
						    	cin >> getProductId;
						    	
						    	cout << "Enter Quantity How much You want: ";
						    	cin >> getQuantity;
							    
								staff.requestSupplier(getProductId,getQuantity);
							}
	                    }while(choiceOperation != 4);
	                }else if(choiceMenuItem == 3){
	                    do{
	                        admin.staffSupplierMenu("supplier");
	                        cout<<"Select operation you want : ";
	                        cin>>choiceOperation;
	                        
	                        if(choiceOperation == 1) {            
	                            srand(time(0));
	                            getSupplierid = rand() % 100 + 1000;
	                           
	                            cout << "Enter Supplier Name: ";
								cin >> getSupplierName;
								
								cout << "Enter Contact Number: ";
								cin >> getContactno;
								
								cout << "Enter Email: ";
								cin >> getEmail;
								
								cout << "Enter Username: ";
								cin >> getUsername;
								
								cout << "Enter Password: ";
								cin >> getPassword;
	                
	                            getStatus = "Active";
	                            admin.addSupplier(getSupplierid, getSupplierName, getContactno, getEmail, 
								getUsername, getPassword, getStatus,"supplier"); 
	                        }else if(choiceOperation == 2) {
	                        	admin.viewSupplier("supplier");
	                        	
	                        	ifstream checkFile("suppliers.txt");
	                        	if(!checkFile || checkFile.peek() == EOF){
	                        		cout<< endl << "No suuppliers available for the Edit"<<endl<< endl;
								}else{
									cout << endl<<"Enter Supplier ID to edit details: ";
	                                cin >> getSupplierid;
	                                  
	                                admin.editSupplierDetails(getSupplierid,"supplier");
								}
                                checkFile.close(); 
	                        }else if(choiceOperation == 3) { 
								admin.viewSupplier("supplier");
	                        	
	                        	ifstream checkFile("suppliers.txt");
	                        	if(!checkFile || checkFile.peek() == EOF){
	                        		cout<< endl << "No suuppliers available for Change Cridentials"<<endl<< endl;
								}else{		
									cout << endl<<"Enter Supplier ID to edit credentials (username/password): ";
									cin >> getSupplierid;
									
									admin.editSupplierCredential(getSupplierid,"supplier"); 
								}
								checkFile.close();
	                        }else if(choiceOperation == 4) {
								admin.viewSupplier("supplier");
	                        	
	                        	ifstream checkFile("suppliers.txt");
	                        	if(!checkFile || checkFile.peek() == EOF){
	                        		cout<< endl << "No suuppliers available for Change status"<<endl<< endl;
								}else{
									cout << endl<<"Enter Supplier ID to change status (Active/Inactive): ";
									cin >> getSupplierid;
									
									admin.editSupplierStatus(getSupplierid,"supplier"); 
								}
								checkFile.close();
							}else if(choiceOperation == 5){
								admin.viewSupplier("supplier");
							}
	                    }while(choiceOperation != 6);
	                }else if(choiceMenuItem == 4){
	                    do{
	                        admin.staffSupplierMenu("staff");
	                        cout<<"Select operation you want : ";
	                        cin>>choiceOperation;
	                        
	                        if(choiceOperation == 1) {            
	                            srand(time(0));
	                            getSupplierid = rand() % 100 + 1000;
	                           
	                            cout << "Enter Staff Name: ";
								cin >> getStaffName;
								
								cout << "Enter Contact Number: ";
								cin >> getContactno;
								
								cout << "Enter Email: ";
								cin >> getEmail;
								
								cout << "Enter Username: ";
								cin >> getUsername;
								
								cout << "Enter Password: ";
								cin >> getPassword;
	                
	                            getStatus = "Active";
	                            admin.addSupplier(getSupplierid, getStaffName, getContactno, getEmail, 
								getUsername, getPassword, getStatus, "staff"); 
	                        }else if(choiceOperation == 2) {
	                        	admin.viewSupplier("staff");
	                        	ifstream checkFile("staff.txt");
	                        	if(!checkFile || checkFile.peek() == EOF){
	                        		cout<< "Staff Not available for edit details.";
								}else{
	                                cout << "Enter Staff ID to edit details: ";
	                                cin >> getSupplierid;
	                                  
	                                admin.editSupplierDetails(getSupplierid,"staff");  
                            	}
                            	checkFile.close();
	                        }else if(choiceOperation == 3) { 
								admin.viewSupplier("staff");
	                        	ifstream checkFile("staff.txt");
	                        	if(!checkFile || checkFile.peek() == EOF){
	                        		cout<< "Staff Not available for edit cridential.";
								}else{		
									cout << "Enter Satff ID to edit credentials (username/password): ";
									cin >> getSupplierid;
									
									admin.editSupplierCredential(getSupplierid,"staff");
								}
	                        }else if(choiceOperation == 4) {
								admin.viewSupplier("staff");
	                        	ifstream checkFile("staff.txt");
	                        	if(!checkFile || checkFile.peek() == EOF){
	                        		cout<< "Staff Not available for edit status.";
								}else{
									cout << "Enter Staff ID to change status (Active/Inactive): ";
									cin >> getSupplierid;
									
									admin.editSupplierStatus(getSupplierid,"staff");
								}
							}else if(choiceOperation == 5){
								admin.viewSupplier("staff");
							}
	                    }while(choiceOperation != 6);
	                }else if(choiceMenuItem == 5){
	                    do{
	                        admin.reportMenu();
	                        cout<<"Select operation you want : ";
	                        cin>>choiceOperation;
	                        
	                        if(choiceOperation == 1) { admin.viewStock(); }
	                        else if(choiceOperation == 2) { supplier.productHistory(); } 
	                        else if(choiceOperation == 3) { staff.viewSalesReport(); }
	                    }while(choiceOperation != 4);
	                }else if(choiceMenuItem == 6){
	                    admin.changePassword();
	                }
	            }while(choiceMenuItem != 7);
			}
        }else if(choiceRole == 2){
            do{
                staffRole();
                cout<<"Select Staff role : ";
                cin>>choicestaffRole;
                
                if( choicestaffRole == 1 ){	
	                loginStatus = login("MANAGER","manager@123");
	        		if(loginStatus){
		                	do{
		                		staff.SalesManagerMenu();
		                		
			                	cout<<"Select Management You want  : ";
			                	cin>>choiceMenuItem;
		                	
		                		if( choiceMenuItem == 1){ admin.viewProduct("manager"); }
								else if( choiceMenuItem == 2){ staff.salesRequest(); }
								else if( choiceMenuItem == 3){ staff.viewSalesReport(); }
								else if( choiceMenuItem == 4){
	        						admin.viewProduct("admin");
	        						
	        						cout << endl<<"Enter Id : ";
							    	cin >> getProductId;
							    	
							    	cout << "Enter Quantity How much You want: ";
							    	cin >> getQuantity;
								    
									staff.requestSupplier(getProductId,getQuantity); 
								}
								else if( choiceMenuItem == 5){
									staff.viewSupplierProduct(); 
								}
								else if( choiceMenuItem == 6){ staff.changePassword(); }
							}while( choiceMenuItem != 7 );
					}
				}else if( choicestaffRole == 2 ){
					loginStatus = login("SALER","saler@123");
	        		if(loginStatus){
						do{
	                		staff.SalesPersonMenu();
	                		
		                	cout<<"Select Management You want  : ";
		                	cin>>choiceMenuItem;
	                	
	                		if( choiceMenuItem == 1){ admin.viewProduct("saler"); }
							else if( choiceMenuItem == 2){
								admin.viewProduct("saler");
								ifstream checkFile("products.txt");
								if(!checkFile || checkFile.peek() == EOF){
									cout<< endl<< "Products Not available for sell"<<endl;
								}else{
									srand(time(0));
	   								currentId = rand() % 1001;
	   								stringstream ss;
	   								ss << setw(4) << setfill('0') << currentId ;
	        						getRequestId = "R" + ss.str();
	        						
									cout<< endl<< "Enter Product Id which you want to sell : ";
									cin>>getProductId;
									
									cout<< endl<< "How much quantity want to sell : ";
									cin>>getSellQuantity;
									
									time_t now = time(0);
									tm *ltm = localtime(&now);
									getDate = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
									
									getStatus = "Pending";
									
									bool getProductFoundStatus = staff.saleProduct(getRequestId,getProductId,getSellQuantity,getDate,getStatus); 
									if( getProductFoundStatus ){
										cout<< "Sales Request Created Successfully..." <<endl;
									}else{
									    cout<< "Product Not found!..." <<endl;
									}
								}
								checkFile.close();
							}
							else if( choiceMenuItem == 3){ 
								staff.viewStatusOfSellingProduct(); 
							}
							else if( choiceMenuItem == 4){ staff.changePassword(); }
						}while( choiceMenuItem != 5 );
					}
				}
        	}while(choicestaffRole != 3);
        }else if(choiceRole == 3){
        	loginStatus = login("SUPPLIER","supplier@123");
        	if(loginStatus){
	            do{
	                supplier.menu();
	                cout<<"Select the management you want : ";
	                cin>>choiceMenuItem;
	                
	                if(choiceMenuItem == 1) { supplier.stockRequest(); }
	                else if(choiceMenuItem == 2) {
					    supplier.stockRequest();
					
					    ifstream checkFile("request_to_suppler.txt");
					    if(!checkFile || checkFile.peek() == EOF){
					        cout << "No Request is created yet for supply." << endl;
					    } else {
					        string getRequestId;
					        cout << endl<< "Enter Request Id which you want to Supply To The Car Inventory : ";
					        cin >> getRequestId;
					        supplier.supplyProduct(getRequestId);
					    }
					    checkFile.close();
					} 
	                else if(choiceMenuItem == 3) { supplier.productHistory(); }
	                else if(choiceMenuItem == 4) { supplier.changePassword(); }
	                else if(choiceMenuItem == 5) {
						do{
	                        admin.productMenu();
	                        cout<<"Select operation you want : ";
	                        cin>>choiceOperation;
	                        
	                        if(choiceOperation == 1) {
	                        	srand(time(0));
								 
   								currentId = rand() % 10 + 1000;
        						getProductId = "P" + to_string(currentId);
								
								cin.ignore();
							    cout << "Enter Product name: ";
							    getline(cin, getProductName);
							
							    cout << "Enter Category ( Engine, Transmission, Brakes, Electrical, Fuel System ): ";
							    getline(cin, getCategory);
							
							    cout << "Enter Brand: ";
							    getline(cin, getBrand);
							
							    cout << "Enter Car Model: ";
							    getline(cin, getModel);
							
							    cout << "Enter Variant (e.g., Petrol/Diesel/EV): ";
							    getline(cin, getVariant);
							
							    cout << "Enter Price (in Rs): ";
							    cin >> getPrice;
							
							    cout << "Enter Quantity in stock: ";
							    cin >> getQuantity;
							
							    cout << "Enter Re-Order Level: ";
							    cin >> getReOrderLevel;
							
							    getLastUpdateDate = "NULL";
							
							    if ( getQuantity < getReOrderLevel ){
							    	getStatus = "Inactive";
								}else{
									getStatus = "Active";
								}
								
								admin.addProduct(getProductId,getProductName,getCategory,getBrand,getModel,getVariant,getPrice,getQuantity,
								getReOrderLevel,getLastUpdateDate,getStatus,"supplier"); 	
							}
	                        else if(choiceOperation == 2) { 
								admin.viewProduct("supplier");
								
							    cout << endl<<"Enter the product Id which you want to Edit : ";
							    cin >> getProductId;
							    
								admin.editProduct(getProductId,"supplier"); 
							} 
	                        else if(choiceOperation == 3) {
	                        	admin.viewProduct("supplier");
	                        	cout<< "Enter the product Id which you want to delete : ";
	                        	cin>> getProductId;
	                        	
								admin.deleteProduct(getProductId,"supplier"); 
							}
	                        else if(choiceOperation == 4) { admin.viewProduct("supplier"); }
	                    }while(choiceOperation != 5);
					}
	        	}while(choiceMenuItem != 6);
	    	}
        }
    }while(choiceRole != 4);
    
    cout<<endl<<endl;
    line();
    cout<< setw(130) <<" || THANK YOU FOR USING INVENTORY MANAEMENT SYSTEM || "<<endl<<endl;
    line();
    return 0;
}
