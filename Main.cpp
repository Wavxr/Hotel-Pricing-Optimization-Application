#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <sstream>
using namespace std;

struct Event {
    string name;
    vector<int> customerCounts;
};
HWND WINAPI GetConsoleWindowNT(void){
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    GetConsoleWindowT GetConsoleWindow;
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib
    ,TEXT("GetConsoleWindow"));
    if(GetConsoleWindow == NULL){
        return NULL;
    }
    return GetConsoleWindow();
}

const int MAX_ROOMS = 24;
const int ROOM_DATA_SIZE = 7;

double rooms[MAX_ROOMS][ROOM_DATA_SIZE] = {
    //roomNumber, fixedPrice, capacity, availability, Fullfeature, bedsize(0twin||1king||2queen), Service(0=no/1=yes)
		{1, 1299.0, 4, 1, 0, 0}, //WIN SIZED BED W/O SERVICE
        {2, 1299.0, 4, 1, 0, 0}, //--
        {3, 1299.0, 4, 1, 0, 0}, //--
        {4, 1299.0, 4, 1, 0, 0}, //--
        {5, 1499.0, 4, 1, 1, 0}, //--------QUEEN SIZED W/O
        {6, 1499.0, 4, 1, 1, 0}, //--
        {7, 1499.0, 4, 1, 1, 0}, //--
        {8, 1499.0, 4, 1, 1, 0},//--
        {9, 1799.0, 4, 1, 2, 0},//--------KING SIZED BED W/O
        {10,1799.0, 4, 1, 2, 0}, //--
        {11,1799.0, 4, 1, 2, 0}, //--
        {12,1799.0, 4, 1, 2, 0}, //--
        {13,1999.0, 4, 1, 3, 0}, //--------TWIN SIZED BED WITH STREAMING
        {14,1999.0, 4, 1, 3, 0}, //--
        {15,1999.0, 4, 1, 3, 0}, //--
        {16,1999.0, 4, 1, 3, 0}, //--
        {17,2199.0, 4, 1, 4, 0}, //---------QUEEN SIZED BED WITH STREAMING
        {18,2199.0, 4, 1, 4, 0},//--
        {19,2199.0, 4, 1, 4, 0},//--
        {20,2199.0, 4, 1, 4, 0},//--
 		{21,2499.0, 4, 1, 5, 0},//---------KING SIZED BED WITH STREAMING
        {22,2499.0, 4, 1, 5, 0},//--
        {23,2499.0, 4, 1, 5, 0},//--
        {24,2499.0, 4, 1, 5, 0}//--
};
class Guest {
	private:
	    string name;
	    int numberOfGuests;
	    string discountType;

	public:
		//constructor
    	Guest(const string& n, int numGuests, string discountType) : name(n), numberOfGuests(numGuests), discountType(discountType) {}

	    // Getters
	    string getName() const { return name; }
	    int getNumberOfGuests() const { return numberOfGuests; }
	    string getDiscountType() const { return discountType; }
};
class Booking {
	private:
	    Guest guest;
	    int roomNumber;
	    double totalPrice;
	    double discountMinus;
		double additionalGuestCharge;
	    double occupancyCharge;
	    double marketAnalysisCharge;
	    string roomPreference;
	
	public:
	    // Constructor
	    Booking(const Guest& g, int roomNum, string roomPref) : guest(g), roomNumber(roomNum), roomPreference(roomPref){}
	
	    // Getters
	    Guest getGuest() const { return guest; }
	    int getRoomNumber() const { return roomNumber; }
	    double getTotalPrice() const { return totalPrice; }
	    double getOccupancyCharge() const { return occupancyCharge; }
	    double getMarketAnalysisCharge() const { return marketAnalysisCharge; }
	    double getAdditionalGuestCharge() const { return additionalGuestCharge; }
	    double getDiscountMinus() const { return discountMinus; }
		string getRoomPreference() const { return roomPreference; }
	    
	    // Setters
	    void setPrice(double price) { totalPrice = price; }
	    void setOccupancyCharge(double charge) { occupancyCharge = charge; }
    	void setMarketAnalysisCharge(double charge) { marketAnalysisCharge = charge; }
    	void setAdditionalGuestCharge(double charge) { additionalGuestCharge = charge; }
    	void setRoomPreference(string roomPref) { roomPreference = roomPref; }
    	void setDiscountMinus(double discount) {discountMinus = discount; }
    	
	    void displayReceipt(int roomNumber) const {
		    cout << setw(30) << left << "Guest Name:" << guest.getName() << endl;
		    cout << setw(30) << left << "Room Number:" << roomNumber << endl;
		    cout << setw(30) << left << "Room Preference:" << roomPreference << endl;
		    cout << setw(30) << left << "Base Price:" << fixed << setprecision(2) << rooms[roomNumber - 1][1] << " PHP" << endl;
		    cout << setw(30) << left << "Additional Guest Charge:" << fixed << setprecision(2) << getAdditionalGuestCharge() << " PHP" << endl;
		    cout << setw(30) << left << "Occupancy Charge:" << fixed << setprecision(2) << getOccupancyCharge() << " PHP" << endl;
		    cout << setw(30) << left << "Market Analysis Charge:" << fixed << setprecision(2) << getMarketAnalysisCharge() << " PHP" << endl;
		    cout << setw(30) << left << "Discount Type: " << fixed << setprecision(2) << guest.getDiscountType() << endl;
		    cout << setw(30) << left << "Saved from Discount: " << fixed << setprecision(2) << getDiscountMinus() << " PHP" << endl;
			cout << setw(30) << left << "Total Price:" << fixed << setprecision(2) << getTotalPrice() << " PHP" << endl;
		}
		void displayReceipt() const {
		    cout << setw(30) << left << "Guest Name:" << guest.getName() << endl;
		    cout << setw(30) << left << "Room Number:" << getRoomNumber() << endl;
		    cout << setw(30) << left << "Room Preference:" << roomPreference << endl;
		    cout << setw(30) << left << "Base Price:" << fixed << setprecision(2) << rooms[getRoomNumber() - 1][1] << " PHP" << endl;
		    cout << setw(30) << left << "Additional Guest Charge:" << fixed << setprecision(2) << getAdditionalGuestCharge() << " PHP" << endl;
		    cout << setw(30) << left << "Occupancy Charge:" << fixed << setprecision(2) << getOccupancyCharge() << " PHP" << endl;
		    cout << setw(30) << left << "Market Analysis Charge:" << fixed << setprecision(2) << getMarketAnalysisCharge() << " PHP" << endl;
		    cout << setw(30) << left << "Discount Type: " << fixed << setprecision(2) << guest.getDiscountType() << endl;
			cout << setw(30) << left << "Saved from Discount: " << fixed << setprecision(2) << getDiscountMinus() << " PHP" << endl;
			cout << setw(30) << left << "Total Price:" << fixed << setprecision(2) << getTotalPrice() << " PHP" << endl;
		}
	    
};
class MarketAnalysis {
	private:
	    vector<Event> dataset;
	    vector<double> increasedPercentage;
			
	    void divideAndConquerMarketAnalysis(int start, int end) {
	        if (start == end) {
	            specificMarketAnalysis(dataset[start]);
	        } else if (start < end) {
	            int mid = start + (end - start) / 2;
	            divideAndConquerMarketAnalysis(start, mid);
	            divideAndConquerMarketAnalysis(mid + 1, end);
	        }
	    }
	public:
	    void loadDataSet(const string& filename) {
	        ifstream file(filename);
	        if (!file.is_open()) {
	            cerr << "Error: Unable to open file." << endl;
	            return;
	        }
	
	        string eventName;
	        int customerCount;
	        while (file >> eventName >> customerCount) {
	            bool found = false;
	            for (auto& event : dataset) {
	                if (event.name == eventName) {
	                    event.customerCounts.push_back(customerCount);
	                    found = true;
	                    break;
	                }
	            }
	            if (!found) {
	                dataset.push_back({eventName, {customerCount}});
	            }
	        }
	        file.close();
	    }	
	    void marketAnalysis() {
	        increasedPercentage.clear();
	        divideAndConquerMarketAnalysis(0, dataset.size() - 1);
	    }	
	    void specificMarketAnalysis(const Event& event) {
	        double totalCustomers = 0;
	        for (int count : event.customerCounts) {
	            totalCustomers += count;
	        }
	        double averageCustomers = totalCustomers / event.customerCounts.size();
	        double normalDay = 20;
	        double increasePercentage = ((averageCustomers - normalDay) / normalDay) * 100.0;
	        increasedPercentage.push_back(increasePercentage);
	    }	
		double getIncreasedPercentage(const string& eventName) {
	        for (size_t i = 0; i < dataset.size(); ++i) {
	            if (dataset[i].name == eventName) {
	                return increasedPercentage[i];
	            }
	        }
	        return -1;
	    }	
	    void displayMarketAnalysis() {
	    	cout<<"\n\n\n\n";
	        cout << "\n                            MARKET ANALYSIS RESULT" << endl << endl;
	        cout << "--------------------------------------------------------------------------------\n";
	        cout << "\t\t"<< left << setw(26) << "Event" << setw(25) << "Increased Percentage" << endl;
	        cout << "--------------------------------------------------------------------------------\n";
	        for (size_t i = 0; i < dataset.size(); ++i) {
	            cout << "\t\t" <<left << setw(30) << dataset[i].name << setw(3) << fixed << setprecision(2) << increasedPercentage[i] << " %" << endl;
	        }
	        cout << "--------------------------------------------------------------------------------\n\n\n\n\n\n\n\n\n\n\n";
	    }
};
class DynamicPricing {
	public:
	    Booking& findBooking(int roomNumber, vector<Booking>& bookings) {
		    auto it = find_if(bookings.begin(), bookings.end(), 
		        [roomNumber](const Booking& booking) { 
		            return booking.getRoomNumber() == roomNumber; 
		        });
		            
		    if (it != bookings.end()) {
		        return *it;
		    } else {
		        throw runtime_error("Room not found.");
		    }
		}	
	    double dynamicPricing(double adjustedPrice, string event, vector<Booking>& bookings, int roomNumber, float discount) {
	        MarketAnalysis marketAnalysis;
	        double basePrice = rooms[roomNumber - 1][1];
	        double tempPrice = rooms[roomNumber - 1][1];
	        double tempPrice2 = rooms[roomNumber - 1][1];
	        double discountMinus = basePrice - rooms[roomNumber - 1][1] * discount;
	        findBooking(roomNumber, bookings).setDiscountMinus(discountMinus);
	        int totalOccupiedRooms = 0;
	        for (int i = 0; i < MAX_ROOMS; ++i) {
	            if (rooms[i][3] == 0) { // Check if room is occupied
	                totalOccupiedRooms++;
	            }
	        }
			//basePrice = 100, adjustedPrice = 140, tempPrice = 100
	        // Adjust price based on occupancy
	        tempPrice *= (1.0 + (totalOccupiedRooms * 0.05)); // Increase price by 5% for each occupied room
	        double occupancyPrice = tempPrice - basePrice;
			findBooking(roomNumber, bookings).setOccupancyCharge(occupancyPrice);
	        // Adjust price based on external events
	        marketAnalysis.loadDataSet("marketData.txt");
	        marketAnalysis.marketAnalysis();
	        double eventImpact = marketAnalysis.getIncreasedPercentage(event) / 100;
	        double percentage = (1 + eventImpact);
	
	        if (eventImpact != -1.0) {
	            cout << "\t\t\tIncreased percentage for " << event << ": " << fixed << setprecision(2) << percentage << "%" << endl;
	        } else {
	            cout << "\t\t\tEvent not found." << endl;
	        }
	        tempPrice2 *= percentage;
	        double demandPrice = tempPrice2 - basePrice;
	    	findBooking(roomNumber, bookings).setMarketAnalysisCharge(demandPrice);
	        return adjustedPrice + occupancyPrice + demandPrice - discountMinus;
	    }
};
class Hotel {
	private:
	    vector<Booking> bookings;
	    DynamicPricing d;
	public:
		void displayAllRooms() {
			cout<<"\n";
	        cout<<"                               DISPLAYING ALL ROOMS        ";
			cout<<"\n\n--------------------------------------------------------------------------------";
		    cout << "\t\t" <<setw(10) << "Room Number" << setw(15) << "Fixed Price" << setw(10) << "Capacity" << setw(15) << "Availability" << setw(15) << "Total Price" << endl;
		    for (int i = 0; i < MAX_ROOMS; ++i) {
		        cout << "\t" <<setw(7) << rooms[i][0] << setw(15) << rooms[i][1] << setw(10) << rooms[i][2] << setw(18) << (rooms[i][3] == 1 ? "Available" : "Occupied") << setw(10) << rooms[i][5]  << endl;
		    }
		    cout<<"--------------------------------------------------------------------------------";
		}
	    Booking& findBooking(int roomNumber) {
        	auto it = find_if(bookings.begin(), bookings.end(), 
				[roomNumber](const Booking& booking) { 
                return booking.getRoomNumber() == roomNumber; 
                });
                
	        if (it != bookings.end()) {
	            return *it; 
	        } else {
	            cout << "\n\t\tRoom not found or room not booked!";
	        }
    	}
	    void bookRoom(const Guest& guest, int roomNumber, string event, string roomPref, float discount) {
	    	if (rooms[roomNumber - 1][3] == 0) {
		        cout << "\t\t\tRoom " << roomNumber << " is already occupied. Please choose another room." << endl;
		        return;
		    }
	        bookings.push_back(Booking(guest, roomNumber, roomPref));
	        double totalPrice = calculateTotalPrice(roomNumber, guest, event, discount);
	        findBooking(roomNumber).setPrice(totalPrice);
	        rooms[roomNumber - 1][2] = guest.getNumberOfGuests();
	        rooms[roomNumber - 1][3] = 0; // Mark room as occupied
	        rooms[roomNumber - 1][5] = totalPrice;
	        cout << "\t\t\tRoom " << roomNumber << " successfully booked!" << endl;
	    }
		double calculateTotalPrice(int roomNumber, const Guest& guest, string event, float discount) {
			double basePrice = rooms[roomNumber - 1][1]; // Get fixed price from room data
	        double adjustedPrice = basePrice;
	        double additionalCharge;
	        if (guest.getNumberOfGuests() > rooms[roomNumber - 1][2]) {
	        	additionalCharge = 150 * (guest.getNumberOfGuests() - rooms[roomNumber - 1][2]);
				adjustedPrice += additionalCharge;
	            Booking& bookingToUpdate = findBooking(roomNumber);
	            bookingToUpdate.setAdditionalGuestCharge(additionalCharge);
	        }
	        adjustedPrice = d.dynamicPricing(adjustedPrice, event, bookings, roomNumber, discount);
	        return adjustedPrice;
	    }	
		void checkoutRoom(int roomNumber) {
		    // Check if the room number is valid
		    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
		        cout << "Invalid room number." << endl;
		        return;
		    }
		    // Check if the room is already available
		    if (rooms[roomNumber - 1][3] == 1) {
		        cout << "Room " << roomNumber << " is already available." << endl;
		        return;
		    }
		
		    // Remove booking associated with the room
		    auto it = std::remove_if(bookings.begin(), bookings.end(), [&](const Booking& booking) {
		        return booking.getRoomNumber() == roomNumber;
		    });
		    bookings.erase(it, bookings.end());
		    rooms[roomNumber - 1][2] = 4;
		    rooms[roomNumber - 1][3] = 1; 
		    cout << "\t\tRoom " << roomNumber << " checked out successfully." << endl;
		}	
		void displayReceipts() const {
			int roomNumber;
		    cout<<"                         DISPLAYING ALL OCCUPIED ROOM DETAILS        ";
			cout<<"\n\n--------------------------------------------------------------------------------";
		    for (const Booking& booking : bookings) {
		        booking.displayReceipt(); // Call displayReceipt on each Booking object
		        cout<<"--------------------------------------------------------------------------------";
		    }
		}
};
class CustomerAllocation{
	public:
		void addCustomer(string name, string choice, int roomPrefNum){
		    ofstream outputFile("customer.txt", ios::app);
		    if(!outputFile){
		        cerr<<"File does not exist yet."<<endl;
		        return;
		    }
		     outputFile << name <<"\t" << choice << "\t" << roomPrefNum << "\n";
		     outputFile.close();
		}
		bool doGuestNameExists(const string& guestName) {
		    ifstream file("customer.txt");
		    string line;
		    while (getline(file, line)) {
		        size_t pos = line.find(' ');
		        if (pos != string::npos) {
		            string name = line.substr(0, pos);
		            if (name == guestName) {
		                return true;
		            }
		        }
		    }
		    return false;
		}
		bool checkCustomer(const string& comparisonString) {
		    ifstream inputFile("customer.txt");
		    string line;
		    while (getline(inputFile, line)) {
		        if (line.find(comparisonString) != string::npos) {
		            return true;
		        }
		    }
		    return false;
		}
		string findRoomDescription(const string& guestName) {
		    ifstream file("customer.txt");
		    string line;
		    while (getline(file, line)) {
		        istringstream iss(line);
		        string name, description;
		        int roomPrefNo;
		        getline(iss, name, '\t'); // Extract guest name
		        getline(iss, description, '\t'); // Extract description
		        iss >> roomPrefNo; // Extract room preference number
		        if (name == guestName) {
		            return description; // Return the description if the guest name matches
		        }
		    }
		    return "GUEST DOESN'T EXIST IN THE LIST";
		}
		int findRoomPreferenceNo(const string& guestName) {
		    ifstream file("customer.txt");
		    string line;
		    while (getline(file, line)) {
		        istringstream iss(line);
		        string name, description;
		        int roomPrefNo;
		        getline(iss, name, '\t'); 
		        getline(iss, description, '\t'); 

		        iss.seekg(-1, ios_base::end);
		        while (iss.peek() != '\t' && iss.tellg() > 0) {
		            iss.seekg(-1, ios_base::cur);
		        }
		        iss >> roomPrefNo; 
		
		        if (name == guestName) {
		            return roomPrefNo; 
		        }
		    }
		    cout << "GUEST DOESN'T EXIST IN THE LIST!";
		}
		void decreasedAvailableRooms(double rooms[][ROOM_DATA_SIZE], int choice,string description) {
		    cout << "Available Rooms for Preference" << endl; 
			cout << description << endl;
		    cout << setw(10) << "Room Number" << setw(15) << " Tentative Price" << setw(10) << "Capacity" << setw(15) << "Availability" << endl;
		    for (int i = 0; i < MAX_ROOMS; ++i) {
		        // Check availability and preference description
		        if (rooms[i][3] == 1 && rooms[i][4] == choice) {
		            cout << setw(10) << rooms[i][0] << setw(15) << rooms[i][1] << setw(10) << rooms[i][2] << setw(15) << "Available" << endl;
		        }
		    }
		}
};
class designFrontEnd{
	public:
		void displayMainMenu(){
			system("cls");
			system("Color 03");
			cout<<"\n\n\n\n";
	        cout<<"                      WELCOME TO HADJI INC. HOTEL MANAGEMENT SYSTEM        ";
			cout<<"\n\n--------------------------------------------------------------------------------";
	        cout<<"\n\n\t\t\t\t   MAIN MENU\n\n";
			Sleep(100);
	        cout<<"                             >  [1] - CHECK AVAILABLE ROOMS\n"; cout<<endl; Sleep(100);
	        cout<<"                             >  [2] - OCCUPIED ROOM DETAILS\n"; cout<<endl; Sleep(100);
	        cout<<"                             >  [3] - CHECK IN\n"; cout<<endl; Sleep(100);
			cout<<"                             >  [4] - CHECK OUT\n"; cout<<endl; Sleep(100);
			cout<<"                             >  [5] - MARKET ANALYSIS\n"; cout<<endl; Sleep(100);
			cout<<"                             >  [0] - EXIT\n"; cout<<endl; Sleep(100);
			cout<<"\n--------------------------------------------------------------------------------";
	        cout<<"\n\t\t\tEnter your choice: ";	
		}	
		string displayGetPossibleEvents(){
			string event;
			int eventChoice;
			system("cls");
			system("Color 03");
			cout<<"\n\n\n\n";
	        cout<<"                                  DIFFERENT EVENTS        ";
			cout<<"\n\n--------------------------------------------------------------------------------";
	        cout<<"\n\n\t\t\t\t   MAIN MENU\n\n";
			Sleep(100);
	        cout<<"                             >  [1] - Christmas"; cout<<endl; Sleep(100);
	        cout<<"                             >  [2] - New Year"; cout<<endl; Sleep(100);
	        cout<<"                             >  [3] - Valentines Day"; cout<<endl; Sleep(100);
			cout<<"                             >  [4] - Easter Sunday"; cout<<endl; Sleep(100);
			cout<<"                             >  [5] - Independence Day"; cout<<endl; Sleep(100);
			cout<<"                             >  [6] - Holy Week"; cout<<endl; Sleep(100);
			cout<<"                             >  [7] - Halloween"; cout<<endl; Sleep(100);
			cout<<"                             >  [8] - Saturday"; cout<<endl; Sleep(100);
			cout<<"                             >  [9] - Sunday"; cout<<endl; Sleep(100);
			cout<<"                             >  [10] - Concerts"; cout<<endl; Sleep(100);
			cout<<"                             >  [11] - Low Demand"; cout<<endl;
			cout<<"                             >  [0] - There's no event"; cout<<endl; Sleep(100);
			cout<<"\n\n--------------------------------------------------------------------------------";
	        cout<<"\n\t\t\tWhat's the event today? : ";
	        cin >> eventChoice;
	        switch (eventChoice) {
                    case 1:
                        event = "Christmas";
                        break;
                    case 2:
                        event = "NewYear";
                        break;
                    case 3:
                        event = "ValentinesDay";
                        break;
                    case 4:
                        event = "EasterSunday";
                        break;
                    case 5:
                        event = "IndependenceDay";
                        break;
                    case 6:
                        event = "HolyWeek";
                        break;
                    case 7:
                        event = "Halloween";
                        break;
                    case 8:
                        event = "Saturday";
                        break;
                    case 9:
                        event = "Sunday";
                        break;
                    case 10:
                        event = "Concerts";
                        break;
                    case 11:
                    	event = "LowDemand";
                    	break;
                    case 0:
                    	event = "NormalDay";
                    	break;
                    default:
                        cout << "Invalid event choice." << endl;
                        break;
                return event;
                }
	        
		}			
		void displayCustomerHistoryMenu(){
			system("cls");
			system("Color 03");
			cout<<"\n\n\n\n";
	        cout<<"                                CUSTOMER HISTORY        ";
			cout<<"\n\n--------------------------------------------------------------------------------\n\n\n";
			Sleep(100);
	        cout<<"                          >  [1] - OLD CUSTOMER"; cout<<endl; Sleep(100);
	        cout<<"                          >  [2] - NEW CUSTOMER"; cout<<endl; Sleep(100);
			cout<<"\n\n--------------------------------------------------------------------------------";
	        cout<<"\n\t\t\tWhat's your history? : ";
		}
		void displayCustomerDiscountMenu(){
			system("cls");
			system("Color 03");
			cout<<"\n\n\n\n";
	        cout<<"                        ELLIGIBLE FOR A DISCOUNT? (20% Discount)        ";
			cout<<"\n\n--------------------------------------------------------------------------------\n\n\n";
	        cout<<"                       >  [1] - PERSON WITH DISABILITY"; cout<<endl; Sleep(100);
	        cout<<"                       >  [2] - SENIOR CITIZEN"; cout<<endl; Sleep(100);
	        cout<<"                       >  [0] - NO DISCOUNT"; cout<<endl; Sleep(100);
			cout<<"\n\n--------------------------------------------------------------------------------";
	        cout<<"\n\t\t\tChoice: ";
		}					
		void displayPreferencesMenu(){
			system("cls");
			system("Color 03");
			cout<<"\n\n\n\n";
	        cout<<"                                ROOM PREFERENCES        ";
			cout<<"\n\n--------------------------------------------------------------------------------\n\n\n";
	        cout<<"     >  [0] - Twin sized beds"; cout<<endl; Sleep(100);
	        cout<<"     >  [1] - Twin sized beds w/ streaming services, Video games"; cout<<endl; Sleep(100);
	        cout<<"     >  [2] - King size bed"; cout<<endl; Sleep(100);
	        cout<<"     >  [3] - Queen size bed"; cout<<endl; Sleep(100);
	        cout<<"     >  [4] - Queen size bed w/ streaming services, Video games"; cout<<endl; Sleep(100);
			cout<<"     >  [5] - King size bed w/ streaming services, Video games"; cout<<endl; Sleep(100);  
			cout<<"\n\n--------------------------------------------------------------------------------";
	        cout<<"\n\t\t\tSelect Preference : ";
		}			
		void loadingScreen(){
		
		char intro[15]="WELCOME TO";
		char intro2[20]="HADJI INC. - HOTEL ";
		char intro3[30]="MANAGEMENT SYSTEM";
		cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t      ";
		
		for(int ctr=0; ctr<strlen(intro);ctr++){ 

			cout<<intro[ctr]<<" "; 
			Sleep(80);
		}
		cout<<"\n\n\n\t\t        ";
		for(int ctr2=0; ctr2<strlen(intro2) ;ctr2++){

			cout<<intro2[ctr2]<<" ";
			Sleep(80);
		}
		cout<<"\n\n\n\t\t       ";
	
		for(int ctr3=0; ctr3<strlen(intro3) ;ctr3++){
		
			cout<<intro3[ctr3]<<" ";
			Sleep(80);
		}
}				
		void loadingbar(){
				for (int i=15;i<=100;i+=5){ 
					system("cls");
					cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t";
					cout<<"  Loading "<<i<<"%";
					cout<<"\n\n\n\n\n\n\t\t";
					char x=176; //an ascii character
					for (int j=0; j<i;j+=2){ //display a block of code that get longer as the loading % is closer to 100
						cout<<x;
					}
					Sleep(100);
				}
			}
		void exitScreen(){
				// This function displays a message to the user upon exiting the program. It includes a decorative design using ASCII characters from the Windows.h library.
				//for design purposes, l1-li2 is an ascii characters in windows.h
				char l1 = 201;
				char l2 = 187;
				char l3 = 200;
				char l4 = 188;
				char li1 = 205;
				char li2 = 186;	
				
			cout<<"\n\n\n\n\n\n\n\n\t\t  Y O U   H A V E   E X I T E D   T H E   A P P.\n\n\n";
                    cout<<"\t\t  "<<l1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<l2<<"\n";
                    cout<<"\t\t  "<<li2<<"       GROUP 6 HOTEL MANAGEMENT SYSTEM     "<<li2<<endl;
                    cout<<"\t\t  "<<li2<<"                   Members                 "<<li2<<endl;
                    cout<<"\t\t  "<<li2<<"-------------------------------------------"<<li2<<endl;
                    cout<<"\t\t  "<<li2<<"           Aguilar, John Waver O.          "<<li2<<endl;
                    cout<<"\t\t  "<<li2<<"           Hardin, Kylle Marius M.         "<<li2<<endl;
                    cout<<"\t\t  "<<li2<<"         Mergano, Andrew Rafael S.A        "<<li2<<endl;
                    cout<<"\t\t  "<<li2<<"             Pecson, Yuri R.               "<<li2<<endl;
                    cout<<"\t\t  "<<li2<<"        Villarina, Dinah Chrishalei.       "<<li2<<endl;
                    cout<<"\t\t  "<<l3<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<li1<<l4;
                    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            }
};
int main() {
	designFrontEnd design;
	Hotel hotel;
	MarketAnalysis analyzer;
	CustomerAllocation customer;
    HWND hWnd = GetConsoleWindowNT();
    MoveWindow(hWnd, 350, 50, 680, 600, TRUE); // Sizing the window for a cleaner look
    
    system("title HOTEL MANAGEMENT SYSTEM");
    system("Color 03");
    design.loadingbar();
	system("cls");
    design.loadingScreen();
	Sleep(300);

    while(1) {
		int choice;
		design.displayMainMenu();
        cin>>choice;
        switch (choice) {
            case 1:{
            	// Check all available rooms
            	int roomNum;
            	system("cls");
                hotel.displayAllRooms();
                cout << "Room detail to check: ";
                cin >> roomNum;
                hotel.findBooking(roomNum).displayReceipt(roomNum);
                system("pause");
                break;
			}
			case 2:{
				//manage room
				system("cls");
				hotel.displayReceipts();
				system("pause");
				break;
			}
			case 3:{
				// Check in
				system("cls");
                string guestName;
                int numberOfGuests;
                int roomNumber;
                int eventChoice;
                int discountChoice;
                string event;
                string description;
                string discountType;
                float discount;
                int newOrOld;
                int roomPref;
				string sameRoomChoice;

                // Input guest details
                cout << "Enter Guest Name: ";
                cin.ignore();
                getline(cin, guestName);
                cout << "Enter Number of Guests: ";
                cin >> numberOfGuests;
                design.displayCustomerDiscountMenu();
                cin >> discountChoice;
                switch(discountChoice){
                	case 1:{
                		discountType = "PWD (20\%)";
                		discount = 0.8;
						break;
					}
					case 2:{
						discountType = "Senior (20\%)";
						discount = 0.8;
						break;
					}
					case 0:{
						discountType = "None";
						discount = 1;
						break;
					}
				}
                
                // Room Allocation
                design.displayCustomerHistoryMenu();
                cin >> newOrOld;
                switch(newOrOld){
                	case 1:{ //OLD CUSTOMER
                		string line;
		    			customer.checkCustomer(guestName);
						if(customer.checkCustomer(guestName)){
					        cout<<"Confirmed!"<<endl;
					        cout<<"Do you want the same Room again?(Yes/No): ";
					        cin >> sameRoomChoice;
					        if(sameRoomChoice == "YES" || sameRoomChoice=="yes"||sameRoomChoice=="y"||sameRoomChoice=="Yes"||sameRoomChoice=="Y"){
					        	description = customer.findRoomDescription(guestName); 
								roomPref = customer.findRoomPreferenceNo(guestName);
					    	} 
							else if(sameRoomChoice=="No"||sameRoomChoice=="no"||sameRoomChoice=="NO"||sameRoomChoice=="n"||sameRoomChoice=="N"){
								design.displayPreferencesMenu();
		                		cin >> roomPref;
		                		switch(roomPref){
		                			case 0:
							            description = "Twin sized beds";
							            break;
							        case 1:
							            description = "Twin sized beds w/ streaming services, Video games.";
							            break;
							        case 2:
							            description = "King size bed";
							            break;
							        case 3:
							            description = "Queen size bed";
							            break;
							        case 4:
							            description = "Queen size bed w/ streaming services, Video games";
							            break;
							        case 5:
							            description = "King size bed w/ streaming services, Video games";
							            break;
							        default:
							            description = "Unknown preference";
							            break;
								}
								}
							}	
						system("cls");
						customer.decreasedAvailableRooms(rooms, roomPref, description);
						cout << "Select a room: ";
						cin >> roomNumber;
						break;
					}
					case 2:{ //NEW CUSTOMER
						design.displayPreferencesMenu();
                		cin >> roomPref;
                		switch(roomPref){
                			case 0:
					            description = "Twin sized beds";
					            break;
					        case 1:
					            description = "Twin sized beds w/ streaming services, Video games.";
					            break;
					        case 2:
					            description = "King size bed";
					            break;
					        case 3:
					            description = "Queen size bed";
					            break;
					        case 4:
							    description = "Queen size bed w/ streaming services, Video games";
							    break;
							case 5:
							    description = "King size bed w/ streaming services, Video games";
							    break;
							default:
							    description = "Unknown preference";
								break;
						}
						system("cls");
						customer.decreasedAvailableRooms(rooms, roomPref, description);
						cout << "Select a room: ";
						cin >> roomNumber;
						customer.addCustomer(guestName, description, roomPref);
						break;
					}
				}
				// Display available events
                event = design.displayGetPossibleEvents();       
                hotel.bookRoom(Guest(guestName, numberOfGuests, discountType), roomNumber, event, description, discount);
				system("pause");
				break;
			}
			case 4: {
			    // Check out
			    system("cls");
			    int roomNumber;
			    cout << "Enter Room Number to check out: ";
			    cin >> roomNumber;
			    hotel.checkoutRoom(roomNumber);
			    system("pause");
			    break;
			}
			case 5: {
				// Market Analysis	
				system("cls");
			    analyzer.loadDataSet("marketData.txt");
			    analyzer.marketAnalysis();
			    analyzer.displayMarketAnalysis();
			    cout << endl;
				system("pause");
				break;
			}
			case 0:{
				system("cls");
        		Sleep(200);
        		design.exitScreen();
        		system("pause");
				exit(0);
				break;
			}
			default:{
				cout << "Invalid choice. Please enter a valid option." << endl;
				break;
			}
        }
    }
    return 0;
}
