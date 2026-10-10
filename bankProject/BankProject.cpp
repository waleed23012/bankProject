
#include <iostream>
#include<vector>
#include<string>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;
struct information_clint {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool if_record_is_deleted = false;
};
struct info_user {
	string username;
	string password;
	int permtion = 0;
	bool if_record_is_deleted = false;

};
enum enPermissions {
	ShowClientList = 1,
	AddNewClient = 2,
	DeleteClient = 4,
	UpdateClientInfo = 8,
	FindClient = 16,
	TransactionScreen = 32,
	ManageUsers = 64
};
bool HasPermission(int userPermissions, enPermissions permission)
{
	return (userPermissions & permission) == permission;
}

int read_positive_number() {
	int num = 0;
	cout << "please enter a positive number : " << endl;
	do {
		cin >> num;
		if (num < 0) {
			cout << "please enter a positive number : " << endl;
		}
	} while (num < 0);
	return num;
}


string to_upper(string s) {
	for (int i = 0; i < s.length(); i++) {
		s[i] = toupper(s[i]);
	}
	return s;
}


string Read_text() {
	cout << "please enter your text : " << endl;
	string s1;

	getline(cin, s1);
	return s1;

}


vector<string> split_string(string s, string sep) {
	vector<string> element;
	int pos = 0;
	string sWord;
	while ((pos = s.find(sep)) != std::string::npos) {
		sWord = s.substr(0, pos);
		if (sWord != "") {
			element.push_back(sWord);

		}
		s.erase(0, pos + sep.length());
	}
	if (s != "") {
		element.push_back(s);

	}
	return element;
}


string invese_replase(vector<string> element) {
	string new_1;
	for (string i : element) {
		new_1 += i + " ";
	}
	new_1 = new_1.substr(0, new_1.length() - 1);
	return new_1;
}


string replace_word(string s, string from, string to, bool match_case = false) {

	vector<string> element = split_string(s, " ");
	string result;
	string target = from;
	if (match_case == false) {
		target = to_upper(target);
	}
	for (string& i : element) {
		string current_word = i;

		if (match_case == false) {
			current_word = to_upper(current_word);
		}
		if (current_word == target) {
			i = to;
		}
	}
	result = invese_replase(element);
	return result;



}


string RemovePunctuationsFromString(string s) {
	string b;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != ',' && s[i] != ';') {
			s.erase(i, 1);

			//b += s[i];

		}

	}
	return b;
}


string convart_user_to_line(info_user new1, string seperator) {
	string s;
	s += new1.username + seperator;
	s += new1.password + seperator;
	s += to_string(new1.permtion);
	return s;
}


string convart_clint_to_line(information_clint new1, string seperator) {
	string s;
	s += new1.AccountNumber + seperator;
	s += new1.PinCode + seperator;
	s += new1.Name + seperator;
	s += new1.Phone + seperator;
	s += to_string(new1.AccountBalance);
	return s;

}


info_user convart_to_struct_info_user(string s, string sep) {
	vector<string> w;
	info_user record;
	w = split_string(s, sep);

	if (w.size() != 3) {
		return record;
	}

	record.username = w[0];
	record.password = w[1];
	record.permtion = stoi(w[2]);

	return record;
}


information_clint convart_to_struct_info_clint(string s, string sep) {
	vector<string> w;
	information_clint record;
	w = split_string(s, sep);
	record.AccountNumber = w[0];
	record.PinCode = w[1];
	record.Name = w[2];
	record.Phone = w[3];
	record.AccountBalance = stod(w[4]);
	return record;


}


void add_data_line_in_to_file(string name_file, string stdatafile) {

	bool needNewLine = false;

	ifstream checkFile(name_file, ios::binary | ios::ate);

	if (checkFile.is_open() && checkFile.tellg() > 0) {
		char lastChar;

		checkFile.seekg(-1, ios::end);
		checkFile.get(lastChar);

		if (lastChar != '\n') {
			needNewLine = true;
		}
	}

	checkFile.close();

	ofstream MyFile(name_file, ios::app);

	if (MyFile.is_open()) {

		if (needNewLine) {
			MyFile << endl;
		}

		MyFile << stdatafile << endl;

		cout << "Added successfully\n";

		MyFile.close();
	}
}

vector<information_clint> transform_from_file_clint_to_vector(string file_name, string sep) {
	fstream my_file;
	string s;
	vector< information_clint> records;
	my_file.open(file_name, ios::in);
	if (my_file.is_open()) {
		while (getline(my_file, s)) {
			records.push_back(convart_to_struct_info_clint(s, sep));

		}
	}
	my_file.close();
	return records;
}


vector<info_user> transform_from_file_user_to_vector(string file_name, string sep)
{
	fstream my_file;
	string s;
	vector<info_user> records;

	my_file.open(file_name, ios::in);

	if (my_file.is_open()) {
		while (getline(my_file, s)) {

			if (s.empty())
				continue;

			vector<string> w = split_string(s, sep);

			if (w.size() != 3)
				continue;

			info_user record =
				convart_to_struct_info_user(s, sep);

			if (record.username.empty() ||
				record.password.empty())
				continue;

			records.push_back(record);
		}
	}

	my_file.close();
	return records;
}

void save_data_to_file_clint(string filename, vector<information_clint>& records, string sep) {
	fstream my_file;
	string wLine;
	my_file.open(filename, ios::out);
	if (my_file.is_open()) {
		for (information_clint i : records) {
			if (i.if_record_is_deleted == false) {
				wLine = convart_clint_to_line(i, sep);
				my_file << wLine << endl;
			}
		}
		my_file.close();
	}

}

void save_data_to_file_user(string filename, vector<info_user>& records, string sep) {
	fstream my_file;
	string wLine;
	my_file.open(filename, ios::out);
	if (my_file.is_open()) {
		for (info_user i : records) {
			if (i.if_record_is_deleted == false) {
				wLine = convart_user_to_line(i, sep);
				my_file << wLine << endl;
			}
		}
		my_file.close();
	}

}


information_clint find_clint_from_Accaount_number(string fileName, string AccuntNumber, string sep) {
	fstream myFile;
	vector<information_clint> record;

	myFile.open(fileName, ios::in);
	if (myFile.is_open()) {
		record = transform_from_file_clint_to_vector(fileName, sep);
		myFile.close();
	}
	for (information_clint& w : record) {
		if (w.AccountNumber == AccuntNumber) {
			return w;
		}
	}
	return information_clint();


}


information_clint find_clint_from_Accaount_number_on_vector(string AccuntNumber, vector<information_clint> records) {
	for (information_clint& i : records) {
		if (i.AccountNumber == AccuntNumber) {
			return i;
		}

	}
	return information_clint();
}

info_user find_user_from_username_number_on_vector(string user, vector<info_user> records) {
	for (info_user& i : records) {
		if (i.username == user) {
			return i;
		}

	}
	return info_user();
}



bool IsUsernameExists(string file_name, string sep, string username)
{
	vector<info_user> users =
		transform_from_file_user_to_vector(file_name, sep);

	for (const info_user& user : users)
	{
		if (user.username == username)
			return true;
	}

	return false;
}


bool if_Username_and_pass_is_true(string name_file_users,string sep,string user_name,string password,info_user& currentUser)
{
	vector<info_user> records =
		transform_from_file_user_to_vector(name_file_users, sep);

	for (info_user& i : records)
	{
		if (i.username == user_name &&
			i.password == password)
		{
			currentUser = i;
			return true;
		}
	}

	return false;
}


information_clint Read_clint() {
	information_clint new1;
	cout << "enter your AccountNumber :";
	getline(cin >> ws, new1.AccountNumber);
	cout << endl << "enter your pin code: ";
	getline(cin, new1.PinCode);
	cout << endl << "enter your Name: ";
	getline(cin, new1.Name);
	cout << endl << "enter your phone : ";
	getline(cin, new1.Phone);

	cout << endl << "enter your AccountBalance: ";
	cin >> new1.AccountBalance;
	return new1;

}


info_user Read_user(string file_name, string sep)
{
	info_user record;

	cout << "Enter Username: ";
	getline(cin >> ws, record.username);

	while (IsUsernameExists(file_name, sep, record.username))
	{
		cout << "Username already exists!\n";
		cout << "Enter another Username: ";
		getline(cin >> ws, record.username);
	}

	cout << "Enter Password: ";
	getline(cin >> ws, record.password);

	return record;
}


int GetUserPermissions()
{
	int permissions = 0;
	char answer;

	cout << "Show Client List? y/n: ";
	cin >> answer;

	if (answer == 'y' || answer == 'Y')
		permissions |= ShowClientList;

	cout << "Add New Client? y/n: ";
	cin >> answer;

	if (answer == 'y' || answer == 'Y')
		permissions |= AddNewClient;

	cout << "Delete Client? y/n: ";
	cin >> answer;

	if (answer == 'y' || answer == 'Y')
		permissions |= DeleteClient;

	cout << "Update Client Info? y/n: ";
	cin >> answer;

	if (answer == 'y' || answer == 'Y')
		permissions |= UpdateClientInfo;

	cout << "Find Client? y/n: ";
	cin >> answer;

	if (answer == 'y' || answer == 'Y')
		permissions |= FindClient;

	cout << "Transaction Screen? y/n: ";
	cin >> answer;

	if (answer == 'y' || answer == 'Y')
		permissions |= TransactionScreen;

	cout << "Manage Users? y/n: ";
	cin >> answer;

	if (answer == 'y' || answer == 'Y')
		permissions |= ManageUsers;

	return permissions;
}


void print_result_clint(information_clint record) {
	cout << " your AccountNumber  :" << record.AccountNumber;
	cout << endl << " your pin code: " << record.PinCode;
	cout << endl << " your Name: " << record.Name;
	cout << endl << " your phone : " << record.Phone;
	cout << endl << " your AccountBalance: " << record.AccountBalance;

}
bool IsAccountNumberExists(string file_name, string sep, string account_number)
{
	vector<information_clint> clients =
		transform_from_file_clint_to_vector(file_name, sep);

	for (const information_clint& client : clients)
	{
		if (client.AccountNumber == account_number)
		{
			return true;
		}
	}

	return false;
}
void print_result_user(info_user record) {
	cout << "==================================" << endl;
	cout << "user name is : " << record.username << endl;
	cout << "password is  : " << record.password << endl;
	cout << "permation is : " << record.permtion << endl;

	cout << "==================================" << endl;

}

void if_clint_exsest(information_clint record, string AccountNumber) {
	if (record.AccountNumber != "") {
		print_result_clint(record);

	}
	else {
		cout << "the clint he\\she has this Accountnumber (" << AccountNumber << ") it's not exest" << endl;
	}
}


void print_record_from_file_clint(string file_name, string sep) {
	vector<information_clint> record;
	record = transform_from_file_clint_to_vector(file_name, sep);

	cout << "                " << "clint list " << record.size() << " clint(s)" << endl;
	cout << "-----------------------------------------------------------------------------------------------------" << endl;

	cout << left
		<< "| " << setw(15) << "AccountNumber"
		<< "| " << setw(15) << "PinCode"
		<< "| " << setw(15) << "Name"
		<< "| " << setw(15) << "Phone"
		<< "| " << setw(15) << "AccountBalance"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------" << endl;
	for (information_clint s : record) {
		cout << "| " << left
			<< setw(15) << s.AccountNumber
			<< "| " << setw(15) << s.PinCode
			<< "| " << setw(15) << s.Name
			<< "| " << setw(15) << s.Phone
			<< "| " << setw(15) << fixed << setprecision(2) << s.AccountBalance << endl;
	}
	cout << "-----------------------------------------------------------------------------------------------------" << endl;

}


void print_record_from_file_user(string file_name, string sep) {
	vector<info_user> record;
	record = transform_from_file_user_to_vector(file_name, sep);

	cout << "                " << "user list " << record.size() << " user(s)" << endl;
	cout << "-----------------------------------------------------------------------------------------------------" << endl;

	cout << left
		<< "| " << setw(15) << "Usernamer"
		<< "| " << setw(15) << "password"
		<< "| " << setw(15) << "permation"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------" << endl;
	for (info_user s : record) {
		cout << "| " << left
			<< setw(15) << s.username
			<< "| " << setw(15) << s.password
			<< "| " << setw(15) << s.permtion
			<< endl;
	}
	cout << "-----------------------------------------------------------------------------------------------------" << endl;

}


void add_clint(string file_name, string sep) {
	char flag = 'y';
	string s;
	int counter = 0;
	information_clint record;
	do {
		counter++;
		system("cls");
		cout << "adding your " << counter << " record : " << endl << endl;
		record = Read_clint();

		if (IsAccountNumberExists(file_name, sep, record.AccountNumber))
		{
			cout << "Account number already exists!\n";
		}
		else
		{
			s = convart_clint_to_line(record, sep);
			add_data_line_in_to_file(file_name, s);
		}
		cout << "do you adding new record (Y/N): " << endl << endl;
		cin >> flag;


	} while (tolower(flag) == 'y');

}


void update_target_record_clint(string account_number, vector<information_clint>& records) {
	for (information_clint& i : records) {
		if (i.AccountNumber == account_number) {

			cout << endl << "enter your pin code: ";
			getline(cin >> ws, i.PinCode);
			cout << endl << "enter your Name: ";
			getline(cin, i.Name);
			cout << endl << "enter your phone : ";
			getline(cin, i.Phone);

			cout << endl << "enter your AccountBalance: ";
			cin >> i.AccountBalance;
			break;
		}
	}
}
void update_target_record_user(string user_name, vector<info_user>& records) {
	for (info_user& i : records) {
		if (i.username == user_name) {

			cout << endl << "enter your password: ";
			getline(cin >> ws, i.password);
			i.permtion = GetUserPermissions();
			
			break;
		}
	}
}


void update_for_in_file_clint(string account_number, string filename, string sep) {

	vector<information_clint> records;

	information_clint record;

	char decision;


	records = transform_from_file_clint_to_vector(filename, sep);

	record = find_clint_from_Accaount_number_on_vector(account_number, records);
	if (record.AccountNumber == "") {
		cout << "this record (" << account_number << ") is'nt exist" << endl;

	}
	else {
		print_result_clint(record);
		cout << endl << "do you want ubdate information in record (y|n): ";
		cin >> decision;
		if (decision != 'y' && decision != 'Y') {

			cout << "you dont need uodate record" << endl;
		}
		else {
			update_target_record_clint(account_number, records);

			save_data_to_file_clint(filename, records, sep);

			cout << "successfuly update" << endl;
		}
	}


}



void delet_record_frome_file_clint(string account_number, string name_file) {
	vector<information_clint> data = transform_from_file_clint_to_vector(name_file, "/##/");
	for (information_clint& i : data) {
		if (i.AccountNumber == account_number) {
			i.if_record_is_deleted = true;
		}
	}
	save_data_to_file_clint(name_file, data, "/##/");

}


void update_account_balansed(string file_name, string sep, string account_number, int add) {
	vector<information_clint> records;
	records = transform_from_file_clint_to_vector(file_name, sep);
	for (information_clint& i : records) {
		if (i.AccountNumber == account_number) {
			i.AccountBalance += add;
		}
	}
	save_data_to_file_clint(file_name, records, sep);
}


void debosite_mony(string file_name, string sep) {
	string account_numder;
	information_clint record;
	char desition;
	int added;
	cout << "please enter your account number : " << endl;
	do {
		getline(cin >> ws, account_numder);
		record = find_clint_from_Accaount_number(file_name, account_numder, sep);
		if (record.AccountNumber != "") {
			cout << "the following are the clint details : " << endl;
			cout << "\n****************************************************" << endl;
			print_result_clint(record);
			cout << "\n****************************************************" << endl;
			break;
		}
		else {
			cout << "the account number is incorrect " << endl;
			cout << "please enter your account number : " << endl;

		}


	} while (true);
	cout << "please enter deposit ammount : " << endl;
	added = read_positive_number();
	cout << " are you sure you want to performe thise transaction (y/n):  " << endl;
	cin >> desition;
	if (desition == 'y' || desition == 'Y') {
		update_account_balansed(file_name, sep, account_numder, added);
		cout << "\nDeposit completed successfully.\n";
		cout << "New Balance = " << record.AccountBalance + added << endl;
	}

}


void total_balances(string file_name, string sep) {
	vector<information_clint> record;
	record = transform_from_file_clint_to_vector(file_name, sep);

	cout << "                " << "balance list " << record.size() << " clint(s)" << endl;
	cout << "-----------------------------------------------------------------------------------------------------" << endl;

	cout << left
		<< "| " << setw(15) << "AccountNumber"
		<< "| " << setw(15) << "Name"
		<< "| " << setw(15) << "AccountBalance"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------" << endl;
	for (information_clint s : record) {
		cout << "| " << left
			<< setw(15) << s.AccountNumber
			<< "| " << setw(15) << s.Name
			<< "| " << setw(15) << fixed << setprecision(2) << s.AccountBalance << endl;
	}
	cout << "-----------------------------------------------------------------------------------------------------" << endl;

}


void withdrow(string file_name, string sep) {
	string account_numder;
	information_clint record;
	char desition;
	int rival;
	cout << "******************************** the withdrow screen ***********************************" << endl << endl;
	cout << "please enter your account number : " << endl;
	do {
		getline(cin >> ws, account_numder);
		record = find_clint_from_Accaount_number(file_name, account_numder, sep);
		if (record.AccountNumber != "") {
			cout << "the following are the clint details : " << endl;
			cout << "\n****************************************************" << endl;
			print_result_clint(record);
			cout << "\n****************************************************" << endl;
			break;
		}
		else {
			cout << "the account number is incorrect " << endl;
			cout << "please enter your account number : " << endl;

		}


	} while (true);
	cout << "please enter withdrow ammount : " << endl;
	rival = read_positive_number();
	while (true) {
		if (rival > record.AccountBalance) {
			cout << "Ammount exceed the balance you can withdraw up to : " << record.AccountBalance << endl;
			cout << "please enter withdrow ammount : " << endl;
			rival = read_positive_number();
		}
		else {
			break;
		}
	}
	cout << " are you sure you want to performe thise transaction (y/n):  " << endl;
	cin >> desition;
	if (desition == 'y' || desition == 'Y') {
		update_account_balansed(file_name, sep, account_numder, (-rival));
		cout << "\nwithdrow completed successfully.\n";
		cout << "New Balance = " << record.AccountBalance - rival << endl;
	}

}


void add_user(string file_name, string sep) {
	char flag = 'y';
	string s;
	int counter = 0;
	info_user record;
	do {
		counter++;
		system("cls");
		cout << "adding your " << counter << " record : " << endl << endl;
		record = Read_user(file_name, sep);
		record.permtion = GetUserPermissions();
		s = convart_user_to_line(record, sep);
		add_data_line_in_to_file(file_name, s);
		cout << "do you adding new record (Y/N): " << endl << endl;
		cin >> flag;


	} while (tolower(flag) == 'y');

}


void delete_record_from_file_user(string file_name, string sep) {
	string chaek_username;
	bool flag = false;
	vector<info_user> records = transform_from_file_user_to_vector(file_name, sep);
	cout << "please enter the username you want to delete it : " << endl;
	getline(cin >> ws, chaek_username);
	for (info_user& i : records) {
		if (i.username == chaek_username) {
			i.if_record_is_deleted = true; 
			flag = true;
			break;
		}

	}
	if(flag == true){
		save_data_to_file_user(file_name, records, sep);
	}
	else {
		cout << "the record isnt exst :(" << endl;

	}





}
void update_for_in_file_user(string username, string filename, string sep) {

	vector<info_user> records;

	info_user record;

	char decision;


	records = transform_from_file_user_to_vector(filename, sep);

	record = find_user_from_username_number_on_vector(username, records);
	if (record.username == "") {
		cout << "this record (" << username << ") is'nt exist" << endl;

	}
	else {
		print_result_user(record);
		cout << endl << "do you want ubdate information in record (y|n): ";
		cin >> decision;
		if (decision != 'y' && decision != 'Y') {

			cout << "you dont need uodate record" << endl;
		}
		else {
			update_target_record_user(username, records);

			save_data_to_file_user(filename, records, sep);

			cout << "successfuly update" << endl;
		}
	}


}
void find_and_print_information_user(string file_name, string sep) {
	string user_target;
	cout << "please enter user : " << endl;

	getline(cin >> ws, user_target);
	
	vector<info_user> records;
	records = transform_from_file_user_to_vector(file_name, sep);
	print_result_user(find_user_from_username_number_on_vector(user_target, records));
}
void manage_user(string file_name, string sep) {
	int sub_choise = 0;
	while(true){

		system("cls");
		cout << "================================" << endl;
		cout << "     manage user menue screen   " << endl;
		cout << "================================" << endl;


		cout << "[1] List user  " << endl;
		cout << "[2] Add new user  " << endl;
		cout << "[3] Delete user  " << endl;
		cout << "[4] Update user  " << endl;
		cout << "[5] Find user  " << endl;
		cout << "[6] Main menue " << endl;

		cout << "please enter your choise from[1] to [6]? ";
		cin >> sub_choise;
		system("cls");
		if (sub_choise == 1) {
			print_record_from_file_user(file_name, sep);
			system("pause");
		}
		if (sub_choise == 2) {
			add_user(file_name, sep);
			system("pause");
		}
		if (sub_choise == 3) {
			delete_record_from_file_user(file_name, sep);
			system("pause");
		}
		if (sub_choise == 4) {
			cout << "please enter user_name : " << endl;
			string update_user;
			getline(cin >> ws, update_user);
			update_for_in_file_user(update_user, file_name, sep);
			system("pause");
		}
		if (sub_choise == 5) {
			find_and_print_information_user(file_name, sep);
			system("pause");
		}
		if (sub_choise == 6) {
			break;
		}
	}

}


void run_project(string name_file_clint,string name_file_user, string sep,const info_user& currentUser) {
	int choise = 0;
	while (choise != 8)
	{
		system("cls");
		cout << "========================================\n";
		cout << "          Main Menu Screen\n";
		cout << "========================================\n";
		cout << "[1] Show Client List.\n";
		cout << "[2] Add New Client.\n";
		cout << "[3] Delete Client.\n";
		cout << "[4] Update Client Info.\n";
		cout << "[5] Find Client.\n";
		cout << "[6] Trancaction screen.\n";
		cout << "[7] Manage user.\n";
		cout << "[8] logout.\n";
		cout << "========================================\n";
		cout << "please enter your choise from[1] to [8]? ";

		cin >> choise;
		system("cls");

		if (choise == 1) {
			if (HasPermission(currentUser.permtion, ShowClientList)) {
				print_record_from_file_clint(name_file_clint, sep);
			}
			else {
				cout << "Access Denied! You don't have permission.\n";
			}
		}
		if (choise == 2)
		{
			if (HasPermission(currentUser.permtion, AddNewClient))
			{
				add_clint(name_file_clint, sep);
			}
			else
			{
				cout << "Access Denied! You don't have permission.\n";
			}
		}
		if (choise == 3) {
			if (!HasPermission(currentUser.permtion, DeleteClient)) {
				cout << "Access Denied! You don't have permission.\n";
			}
			else {
				char flage = 'y';
				int counter = 0;
				string account_number;
				do {
					counter++;
					system("cls");
					cout << "please enter your Account number you want to delete it: " << endl << endl;
					getline(cin >> ws, account_number);
					delet_record_frome_file_clint(account_number, name_file_clint);
					cout << "do you want to delete another record (y/n) : " << endl << endl;
					cin >> flage;

				} while (tolower(flage) == 'y');
			}
			}
			if (choise == 4) {
				if (!HasPermission(currentUser.permtion, UpdateClientInfo)) {
					cout << "Access Denied! You don't have permission.\n";
				}
			else{
					char flage = 'y';
					int counter = 0;
					string account_number;
					do {
						counter++;
						system("cls");
						cout << "please enter your Account number you want to Update it: " << endl << endl;
						getline(cin >> ws, account_number);
						update_for_in_file_clint(account_number, name_file_clint, sep);
						cout << "do you want to update another record (y/n) : " << endl << endl;
						cin >> flage;

					} while (tolower(flage) == 'y');

				}
		}

		if (choise == 5) {
			if (!HasPermission(currentUser.permtion, FindClient)) {
				cout << "Access Denied! You don't have permission.\n";
			}
		
		else{
				string account_number;
				information_clint record;
				cout << "please enter the account number you will to find it : " << endl;
				getline(cin >> ws, account_number);
				record = find_clint_from_Accaount_number(name_file_clint, account_number, sep);
				print_result_clint(record);
			}

		}
		if (choise == 6) {
			int sub_choise = 0;
			if (!HasPermission(currentUser.permtion, TransactionScreen)) {
				cout << "Access Denied! You don't have permission.\n";
			}
		else{
				while (sub_choise != 4) {
					system("cls");
					cout << "*************************************************" << endl;
					cout << "                   Trancaction screen                " << endl;
					cout << "*************************************************" << endl;
					cout << "[1] Show debosite mony screen.\n";
					cout << "[2] show withdrow mony screen.\n";
					cout << "[3] Total balances.\n";
					cout << "[4] Main menue.\n";
					cout << "*************************************************" << endl;
					cout << "please enter your choise from[1] to [4]? ";
					cin >> sub_choise;
					system("cls");
					if (sub_choise == 1) {
						debosite_mony(name_file_clint, sep);
						system("pause");
					}
					if (sub_choise == 2) {
						withdrow(name_file_clint, sep);
						system("pause");
					}
					if (sub_choise == 3) {
						total_balances(name_file_clint, sep);
						system("pause");
					}
					if (sub_choise == 4) {
						cout << "-------------------------------------" << endl;
						cout << "Trancaction screen end :)" << endl;
						cout << "-------------------------------------" << endl;
						break;
						system("pause");
					}
				}

			}


		}
		if (choise == 7) {
			if (!HasPermission(currentUser.permtion, ManageUsers)) {
				cout << "Access Denied! You don't have permission.\n";
			}
		else{
				manage_user(name_file_user, sep);
			}
		}
		if (choise == 8) {
			cout << "Logout successfully!\n";
			break;
		}
		system("pause");
	}
}


void loin_screen(string name_file_clint, string name_file_users, string sep)
{
	string user_name;
	string password;
	info_user r; 
	while (true)
	{
		system("cls");

		cout << "-------------------------\n";
		cout << "      Login screen\n";
		cout << "-------------------------\n";

		cout << "Enter your username: ";
		getline(cin >> ws, user_name);

		cout << "Enter your password: ";
		getline(cin >> ws, password);

		if (if_Username_and_pass_is_true(
			name_file_users, sep, user_name, password,r))
		{
			run_project(name_file_clint, name_file_users, sep,r);
		}
		else
		{
			cout << "\nInvalid username or password!\n";
			system("pause");
		}
	}
}

int main()
{
	loin_screen("ClientsData.txt", "users.txt", "/##/");
	return 0;
}
