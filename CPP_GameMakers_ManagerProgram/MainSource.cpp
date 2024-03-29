#include <iostream>
#include <cstring>
#include <string>
#include <windows.h>
#include <fstream>
#include "DoubleLinkedListSource.h" // 檜醞翱唸 葬蝶お 婦溼
#include "AttendanceInteraction.h" // 轎戮 婦溼

using namespace std;

/*霜鼠 薑爾*/
enum DepartmentType {
	TYPE_DEVELOPER, // 偃嫦
	TYPE_DESIGNER, // 蛤濠檜傘
	TYPE_PLANNER // 晦�嘛�
};

#pragma region Methods

/*Form菟*/
void InputForm(); // 殮溘 イ
void OutputForm(int x); // 嬴醒 籀葬 イ
void CostEnterForm(); // 雖陝綠 殮溘イ
void isEmpty(); // 綴 奢除 檜漸お

/*л熱菟*/
void EnterData(); // 等檜攪 殮溘
void PrintData(); // 等檜攪 轎溘
void DeleteData(); // 等檜攪 餉薯
void CostEnterData(int x); // 雖陝綠 殮溘

#pragma endregion

/*陳瞼 婦溼 贗楚蝶*/
class DateClass
{
protected:
	Dates _dates;

public:
	virtual void DateSetting(Dates date) = 0;
	virtual void IfDateEnterSet(Dates date) = 0;
	virtual void ErrorEvent() = 0;
};

/*濰模 婦溼 贗楚蝶*/
class PlaceClass
{
protected:
	string _placeName;

public:
	virtual void PlaceSetting(string Pname) = 0;
};

/*轎戮婦溼 贗楚蝶*/
class AttendanceClass : public DateClass, public PlaceClass
{
public:
	void AttendanceFormInput();
	void AttendanceFormOutput(int type);

	void AttendanceEnter();
	void AttendancePrintForm();
	void AttendancePrint(int placetype);

	void DateSetting(Dates date);
	void IfDateEnterSet(Dates date);
	void ErrorEvent();

	void PlaceSetting(string Pname);
};

/*轎戮 詭景 イ*/
void AttendanceClass::AttendanceFormInput() {
	int jobType;

	system("cls");
	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛1. 轎戮 殮溘                          弛" << endl;
	cout << "弛2. 轎戮 褻��                          弛" << endl;
	cout << "弛0. 菴煎 陛晦                          弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
	cout << " => ";
	cin >> jobType;

	AttendanceFormOutput(jobType);
}

/*轎戮 詭景 嬴醒 イ*/
void AttendanceClass::AttendanceFormOutput(int type) {

	switch (type)
	{
	case 0:
		InputForm();
		break;
	case 1:
		AttendanceEnter();
		break;
	case 2:
		AttendancePrintForm();
		break;
	default:
		while (!(type >= 0 && type < 3))
		{
			cout << "澀跤脹 高擊 殮溘ж樟蝗棲棻." << endl;
			cout << "棻衛 殮溘ж撮蹂 : ";
			cin >> type;
			cout << endl;
		}
		AttendanceFormOutput(type);

		break;
	}
}

/*轎戮 薑爾 殮溘*/
void AttendanceClass::AttendanceEnter() {
	Dates current_Date;
	string currentPlaceName;
	string attendanceSymbol;

	int index = 0;

	Node* temp = peopleList->head;

	system("cls");

	if (peopleList->head->next == peopleList->tail) { // 等檜攪陛 橈棻賊
		return isEmpty();
	}

	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛=> 陳瞼 殮溘                          弛" << endl;
	cout << "弛=> (喇紫 - 錯 - 橾 牖戲煎)            弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
	cout << " => ";
	cin >> current_Date.year;
	cin >> current_Date.month;
	cin >> current_Date.day;

	IfDateEnterSet(current_Date);
	DateSetting(current_Date);

	cin.ignore();

	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛=> 濰模 殮溘                          弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
	cout << " => ";
	getline(cin, currentPlaceName);

	PlaceSetting(currentPlaceName);

	system("cls");

	cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
	cout << "=> "<< current_Date.year << " 喇 " << current_Date.month << " 錯 " << current_Date.day << " 橾" << "" << endl;
	cout << "=> 濰模 " << currentPlaceName << endl;
	cout << "=> (O 轎戮 / 雖陝 X 唸戮)              " << endl;
	cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;

	while (temp->next != peopleList->tail) { // 棻擠 等檜攪陛 橈擊 陽 梱雖

		cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
		cout << "弛檜葷 : " << temp->next->peopleData.name << "                         弛" << endl;
		cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
		cout << " => ";
		cin >> attendanceSymbol;

		cout << endl;

		while (!(attendanceSymbol == "O" || attendanceSymbol == "/" || attendanceSymbol == "X")) {
			cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
			cout << "弛=> 晦�ㄧ� 澀跤殮溘ц蝗棲棻.           弛" << endl;
			cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
			cout << " 棻衛 殮溘 => ";
			cin >> attendanceSymbol;
		}

		AttendanceInformation[currentFilled - 1].atten_Symbol[index++] = attendanceSymbol;

		temp = temp->next;
	}

	AttendanceFormInput();
}

/*轎戮 薑爾 轎溘 イ*/
void AttendanceClass::AttendancePrintForm() {
	int index = 0;

	int placetype;

	system("cls");

	if (!currentFilled) { // 濰模 等檜攪陛 橈棻賊
		return isEmpty();
	}

	while (index < currentFilled) // 濰模 等檜攪偎熱 虜躑
	{
		cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
		cout << " 陳瞼 " << GetPeopleDates[index].year << "喇 " << GetPeopleDates[index].month << "錯 " << GetPeopleDates[index].day << "橾 " << endl;
		cout << " " << index + 1 << ". " << AttendanceInformation[index].PlaceName << endl;
		cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl << endl;

		index++;
	}

	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛=> 橫蛤 濰模陛 掙旎 ж撮蹂?           弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
	cout << " => ";
	cin >> placetype;

	cout << endl;

	while (!(placetype >= 1 && placetype <= currentFilled)) {
		cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
		cout << "弛=> 澀跤殮溘ж樟蝗棲棻.                弛" << endl;
		cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
		cout << " 棻衛 殮溘 => ";
		cin >> placetype;
	}

	AttendancePrint(placetype);
}

/*轎戮 薑爾 轎溘*/
void AttendanceClass::AttendancePrint(int placetype) {
	int index = 0;
	Node* temp = peopleList->head;

	bool replay;

	system("cls");

	while (temp->next != peopleList->tail) { // 等檜攪陛 橈擊 陽 梱雖
		string currentAT_Type;
		currentAT_Type.clear();

		if (!AttendanceInformation[placetype - 1].atten_Symbol[index].compare("O")) {
			currentAT_Type = "轎戮";
		}
		else if (!AttendanceInformation[placetype - 1].atten_Symbol[index].compare("/")) {
			currentAT_Type = "雖陝";
			temp->next->peopleData.haveCost -= 2000;
		}
		else if(!AttendanceInformation[placetype - 1].atten_Symbol[index].compare("X")){
			currentAT_Type = "唸戮";
			temp->next->peopleData.haveCost -= 2000;
		}
		cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
		cout << "弛檜葷 : " << temp->next->peopleData.name << " 轎戮 罹睡 : " << currentAT_Type << "        弛" << endl;
		cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;

		index++;

		temp = temp->next;
	}

	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛1. 棻衛 爾晦                          弛" << endl;
	cout << "弛0. 菴煎 陛晦                          弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
	cout << " => ";
	cin >> replay;

	if (replay) AttendancePrint(placetype);
	else AttendanceFormInput();

}

/*陳瞼 殮溘 褻勒 匐餌*/
void AttendanceClass::IfDateEnterSet(Dates date) {
	if ((date.year % 4 == 0 && date.year % 100 != 0 || date.year % 400 == 0)) { // 彌喇橾 陽
		if ((date.month >= 1 && date.month < 13)) {
			if (date.month != 2) { // 2錯檜 嬴棋 殖
				if (date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12) {
					if (!(date.day >= 1 && date.day < 32)) {
						ErrorEvent();

						return AttendanceEnter();
					}
				}
				else {
					if (!(date.day >= 1 && date.day < 31)) {
						ErrorEvent();

						return AttendanceEnter();
					}
				}
			}
			else { // 2錯
				if (!(date.day >= 1 && date.day < 30)) {
					ErrorEvent();

					return AttendanceEnter();
				}
			}
		}
		else {
			ErrorEvent();

			return AttendanceEnter();
		}
	}
	else { // 彌喇檜 嬴棍 陽
		if ((date.month >= 1 && date.month < 13)) {
			if (date.month != 2) {
				if (date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12) {
					if (!(date.day >= 1 && date.day < 32)) {
						ErrorEvent();

						return AttendanceEnter();
					}
				}
				else {
					if (!(date.day >= 1 && date.day < 31)) {
						ErrorEvent();

						return AttendanceEnter();
					}
				}
			}
			else {
				if (!(date.day >= 1 && date.day < 29)) {
					ErrorEvent();

					return AttendanceEnter();
				}
			}
		}
		else {
			ErrorEvent();

			return AttendanceEnter();
		}
	}

	return;
}

/*縑楝 檜漸お*/
void AttendanceClass::ErrorEvent() {
	system("cls");
	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛=> 陳瞼蒂 澀跤殮溘ц蝗棲棻.           弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
	Sleep(3000);
}

/*陳瞼 等檜攪 撮た*/
void AttendanceClass::DateSetting(Dates date) { 
	_dates = date;

	for (int i = 0; i < MAX_ATTENDANCE_NUMBER; i++) {
		if (GetPeopleDates[i].year == NULL) { // 綠橫氈朝 夠睡攪 厥橫邀
			GetPeopleDates[i] = _dates;
			return;
		}
	}
}

/*濰模 等檜攪 撮た*/
void AttendanceClass::PlaceSetting(string Pname) {
	_placeName = Pname;

	for (int i = 0; i < MAX_ATTENDANCE_NUMBER; i++) {
		if (AttendanceInformation[i].PlaceName.empty()) { // 綠橫氈朝 夠 睡攪 厥橫邀
			PlaceName[i] = _placeName;
			AttendanceInformation[i].PlaceName = _placeName;
			currentFilled++; // 濰模 偎熱 隸陛

			return;
		}
	}
}

#pragma region InitSetting

/*蟾晦 等檜攪 й渡 贗楚蝶*/
class InitSetting
{
public:
	InitSetting();
};

/*蟾晦 等檜攪 й渡 儅撩濠*/
InitSetting::InitSetting()
{
	for (int i = 0; i < MAX_PEOPLE_NUMBER; i++) {
		peopleList->endInsert(EarlyData[i]); // 蟾晦等檜攪 鳶殮
	}
	for (int i = 0; i < MAX_ATTENDANCE_NUMBER; i++) {
		AttendanceInformation[i].PlaceName.clear(); // 濰模 等檜攪 贗萼
	}
}

#pragma endregion

/* Main睡碟 */
int main()
{
	InitSetting Initmachine; // 蟾晦 等檜攪 儅撩

	int jobTypeNumber;

	while (true) // 鼠и瑞Щ
	{
		InputForm();

		cout << "錳ж衛朝 濛機擊 殮溘ж撮蹂 : ";
		cin >> jobTypeNumber;
		cout << endl;

		OutputForm(jobTypeNumber);
	}
	return 0;
}

/* InputForm 睡碟 */
void InputForm() {
	system("cls");
	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛                                      弛" << endl;
	cout << "弛      < Game Makers 轎戮婦葬 >        弛" << endl;
	cout << "弛                                      弛" << endl;
	cout << "弛1. �蛾� 薑爾 殮溘                     弛" << endl;
	cout << "弛2. �蛾� 薑爾 轎溘                     弛" << endl;
	cout << "弛3. �蛾� 薑爾 餉薯                     弛" << endl;
	cout << "弛4. 雖陝綠 婦溼                        弛" << endl;
	cout << "弛5. 轎戮薑爾 婦溼                      弛" << endl;
	cout << "弛0. Щ煎斜極 謙猿                      弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
}

/* Output 睡碟 */
void OutputForm(int numberType) {
	AttendanceClass Attenmachine;

	switch (numberType)
	{
	case 0:
		cout << "Щ煎斜極擊 謙猿ж啊蝗棲棻." << endl;
		exit(1);
		break;
	case 1:
		EnterData();
		break;
	case 2:
		PrintData();
		break;
	case 3:
		DeleteData();
		break;
	case 4:
		CostEnterForm();
		break;
	case 5:
		Attenmachine.AttendanceFormInput();
		break;
	default:
		while (!(numberType >= 0 && numberType < 6))
		{
			cout << "澀跤脹 高擊 殮溘ж樟蝗棲棻." << endl;
			cout << "棻衛 殮溘ж撮蹂 : ";
			cin >> numberType;
			cout << endl;
		}
		OutputForm(numberType);
		break;
	}
}

/* 等檜攪 鳶殮睡碟 (爾諫)*/
void EnterData() {
	int E_age;
	string E_name;
	int E_dept;

	Profile currentPeople;

	Node* temp = peopleList->head;

	int overflow = 0;

	system("cls");

	while (temp->next != peopleList->tail) {

		temp = temp->next;

		if (temp->peopleData.age != NULL) overflow++;

		currentDataPeoples = overflow;

		if (overflow >= MAX_PEOPLE_NUMBER) {
			currentDataPeoples = MAX_PEOPLE_NUMBER;
			cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
			cout << "弛等檜攪陛 粗學 獺蝗棲棻.               弛" << endl;
			cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
			Sleep(2000);

			return;
		}

	}

	if (peopleList->head->next == peopleList->tail) {
		isEmpty();
	}

	for (int i = currentDataPeoples; i < MAX_PEOPLE_NUMBER; i++) {
		
		cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
		 printf("弛=> %2d廓 簞 等檜攪 殮溘                弛\n", i + 1);
		cout << "弛=> 檜葷 - 釭檜 - 霜鼠 牖              弛" << endl;
		cout << "弛=> 偃嫦 : 1 / 蛤濠檣 : 2 / 晦�� : 3   弛" << endl;
		cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;

		cout << "檜葷 : ";
		cin >> E_name;
		currentPeople.name = E_name;

		cout << "釭檜 : ";
		cin >> E_age;
		currentPeople.age = E_age;

		cout << "霜鼠 : ";
		cin >> E_dept;

		while (!(E_dept > 0 && E_dept < 4)) {
			cout << "霜鼠蒂 澀跤殮溘ж樟蝗棲棻." << endl;
			cout << "霜鼠 棻衛殮溘 : ";
			cin >> E_dept;
		}

		currentPeople.department = E_dept;
		currentPeople.haveCost = 20000;

		peopleList->endInsert(currentPeople);
	}
}

/* 等檜攪 轎溘睡碟*/
void PrintData() {
	string currentDept;
	bool replay;

	Node* temp = peopleList->head;

	if (peopleList->head->next == peopleList->tail) { // 等檜攪陛 嬴霜 菟橫鬲雖 彊懊棻賊
		return isEmpty();
	}

	system("cls");
	while (temp->next != peopleList->tail) { // 棻擠 等檜攪陛 橈擊 陽 梱雖

		if (temp->next->peopleData.department == TYPE_DEVELOPER + 1) {
			currentDept = "偃嫦";
		}
		else if (temp->next->peopleData.department == TYPE_DESIGNER + 1) {
			currentDept = "斜葡";
		}
		else {
			currentDept = "晦��";
		}
		cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
		cout << "弛檜葷 : " << temp->next->peopleData.name << "                         弛" << endl;
		 printf("弛釭檜 : %2d 髦                          弛\n", temp->next->peopleData.age);
		cout << "弛霜鼠 : " << currentDept << "                           弛" << endl;
		cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;

		temp = temp->next;
	}

	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛1. 棻衛 爾晦                          弛" << endl;
	cout << "弛0. 菴煎 陛晦                          弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
	cout << " => ";
	cin >> replay;

	if (replay) PrintData();
	else return;
}

/*か薑 等檜攪 餉薯睡碟*/
void DeleteData() {
	system("cls");

	string findName;

	string currentSymbol;

	Node* temp = peopleList->head;

	int count = 0;

	if (peopleList->head->next == peopleList->tail) { // 等檜攪陛 嬴霜 菟橫鬲雖 彊懊棻賊
		return isEmpty();
	}

	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛=> 援掉 餉薯 й 疵陛蹂?               弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
	cout << "檜葷 => ";
	cin >> findName;

	while (temp->next != peopleList->tail) { // 棻擠 等檜攪陛 橈擊 陽 梱雖

		temp = temp->next;

		if (!temp->peopleData.name.compare(findName)) {
			temp->selvDelete();

			currentDataPeoples--;

			for (int i = 0; i < MAX_ATTENDANCE_NUMBER; i++) { // 餉薯陛 檜瑞橫 雖賊 轎戮紫 餉薯
				for (int j = count; j < MAX_ATTENDANCE_NUMBER; j++) {
					AttendanceInformation[i].atten_Symbol[j] = AttendanceInformation[i].atten_Symbol[j + 1];
				}
			}

			cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
			cout << "弛=> 餉薯 腎歷蝗棲棻.                   弛" << endl;
			cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;

			Sleep(2000);

			return;
		}

		count++;
	}

	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛=> п渡 檜葷檜 橈蝗棲棻.              弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;

	Sleep(2000);

}

/*雖陝綠 籀葬 イ 睡碟*/
void CostEnterForm() {
	int jobType;

	if (peopleList->head->next == peopleList->tail) {
		return isEmpty();
	}

	system("cls");

	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛1. 雖陝綠 薑爾 轎溘                   弛" << endl;
	cout << "弛2. 雖陝綠 餉薯                        弛" << endl;
	cout << "弛0. 菴煎陛晦                           弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
	cout << " => ";
	cin >> jobType;

	CostEnterData(jobType);
}

/*雖陝綠 籀葬 等檜攪 睡碟 */
void CostEnterData(int jobType) {
	system("cls");

	string findName;
	bool replay;

	Node* temp = peopleList->head;

	switch (jobType)
	{
	case 0:
		return;

	case 1:
		while (temp->next != peopleList->tail) {

			cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
			cout << "弛檜葷 : " << temp->next->peopleData.name << "                         弛" << endl;
			printf("弛陴擎 雖陝綠 : %5d 錳                弛\n", temp->next->peopleData.haveCost);
			cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;

			temp = temp->next;
		}

		cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
		cout << "弛1. 棻衛 爾晦                          弛" << endl;
		cout << "弛0. 菴煎 陛晦                          弛" << endl;
		cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
		cout << " => ";
		cin >> replay;

		if (replay) CostEnterData(jobType);
		else return CostEnterForm();

		break;

	case 2:
		cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
		cout << "弛=> 援掉 離馬 й 疵陛蹂?               弛" << endl;
		cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
		cout << "檜葷 => ";
		cin >> findName;

		temp = peopleList->head;

		do {
			temp = temp->next;

			if (!temp->peopleData.name.compare(findName)) {
				temp->peopleData.haveCost -= 2000;

				cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
				cout << "弛=> 離馬 腎歷蝗棲棻.                   弛" << endl;
				cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;

				Sleep(2000);

				return CostEnterForm();
			}

		} while (temp->next != peopleList->tail);


		cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
		cout << "弛=> п渡 檜葷檜 橈蝗棲棻.              弛" << endl;
		cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;

		Sleep(2000);

		CostEnterForm();

		break;

	default:
		while (!(jobType >= 0 && jobType <= 2)) {
			cout << "澀跤脹 高擊 殮溘ж樟蝗棲棻." << endl;
			cout << "棻衛 殮溘ж撮蹂 : ";
			cin >> jobType;
		}
		break;
	}

}

/*奢寥 檜漸お 籀葬 睡碟*/
void isEmpty() {
	system("cls");
	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛嬴霜 等檜攪陛 橈蝗棲棻.               弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl << endl;
	Sleep(2000);
}
