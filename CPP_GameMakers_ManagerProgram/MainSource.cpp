#include <iostream>
#include <cstring>
#include <string>
#include <windows.h>
#include <fstream>
#include "DoubleLinkedListSource.h" // ÀÌÁß¿¬°á ¸®½ºÆ® °ü·Ã
#include "AttendanceInteraction.h" // Ãâ¼® °ü·Ã

using namespace std;

/*Á÷¹« Á¤º¸*/
enum DepartmentType {
	TYPE_DEVELOPER, // °³¹ß
	TYPE_DESIGNER, // µðÀÚÀÌ³Ê
	TYPE_PLANNER // ±âÈ¹ÀÚ
};

#pragma region Methods

/*Formµé*/
void InputForm(); // ÀÔ·Â Æû
void OutputForm(int x); // ¾Æ¿ô Ã³¸® Æû
void CostEnterForm(); // Áö°¢ºñ ÀÔ·ÂÆû
void isEmpty(); // ºó °ø°£ ÀÌº¥Æ®

/*ÇÔ¼öµé*/
void EnterData(); // µ¥ÀÌÅÍ ÀÔ·Â
void PrintData(); // µ¥ÀÌÅÍ Ãâ·Â
void DeleteData(); // µ¥ÀÌÅÍ »èÁ¦
void CostEnterData(int x); // Áö°¢ºñ ÀÔ·Â

#pragma endregion

/*³¯Â¥ °ü·Ã Å¬·¡½º*/
class DateClass
{
protected:
	Dates _dates;

public:
	virtual void DateSetting(Dates date) = 0;
	virtual void IfDateEnterSet(Dates date) = 0;
	virtual void ErrorEvent() = 0;
};

/*Àå¼Ò °ü·Ã Å¬·¡½º*/
class PlaceClass
{
protected:
	string _placeName;

public:
	virtual void PlaceSetting(string Pname) = 0;
};

/*Ãâ¼®°ü·Ã Å¬·¡½º*/
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

/*Ãâ¼® ¸Þ´º Æû*/
void AttendanceClass::AttendanceFormInput() {
	int jobType;

	system("cls");
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢1. Ãâ¼® ÀÔ·Â                          ¦¢" << endl;
	cout << "¦¢2. Ãâ¼® Á¶È¸                          ¦¢" << endl;
	cout << "¦¢0. µÚ·Î °¡±â                          ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
	cout << " => ";
	cin >> jobType;

	AttendanceFormOutput(jobType);
}

/*Ãâ¼® ¸Þ´º ¾Æ¿ô Æû*/
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
			cout << "Àß¸øµÈ °ªÀ» ÀÔ·ÂÇÏ¼Ì½À´Ï´Ù." << endl;
			cout << "´Ù½Ã ÀÔ·ÂÇÏ¼¼¿ä : ";
			cin >> type;
			cout << endl;
		}
		AttendanceFormOutput(type);

		break;
	}
}

/*Ãâ¼® Á¤º¸ ÀÔ·Â*/
void AttendanceClass::AttendanceEnter() {
	Dates current_Date;
	string currentPlaceName;
	string attendanceSymbol;

	int index = 0;

	Node* temp = peopleList->head;

	system("cls");

	if (peopleList->head->next == peopleList->tail) { // µ¥ÀÌÅÍ°¡ ¾ø´Ù¸é
		return isEmpty();
	}

	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢=> ³¯Â¥ ÀÔ·Â                          ¦¢" << endl;
	cout << "¦¢=> (³âµµ - ¿ù - ÀÏ ¼øÀ¸·Î)            ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
	cout << " => ";
	cin >> current_Date.year;
	cin >> current_Date.month;
	cin >> current_Date.day;

	IfDateEnterSet(current_Date);
	DateSetting(current_Date);

	cin.ignore();

	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢=> Àå¼Ò ÀÔ·Â                          ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
	cout << " => ";
	getline(cin, currentPlaceName);

	PlaceSetting(currentPlaceName);

	system("cls");

	cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
	cout << "=> "<< current_Date.year << " ³â " << current_Date.month << " ¿ù " << current_Date.day << " ÀÏ" << "" << endl;
	cout << "=> Àå¼Ò " << currentPlaceName << endl;
	cout << "=> (O Ãâ¼® / Áö°¢ X °á¼®)              " << endl;
	cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;

	while (temp->next != peopleList->tail) { // ´ÙÀ½ µ¥ÀÌÅÍ°¡ ¾øÀ» ¶§ ±îÁö

		cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
		cout << "¦¢ÀÌ¸§ : " << temp->next->peopleData.name << "                         ¦¢" << endl;
		cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
		cout << " => ";
		cin >> attendanceSymbol;

		cout << endl;

		while (!(attendanceSymbol == "O" || attendanceSymbol == "/" || attendanceSymbol == "X")) {
			cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
			cout << "¦¢=> ±âÈ£¸¦ Àß¸øÀÔ·ÂÇß½À´Ï´Ù.           ¦¢" << endl;
			cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
			cout << " ´Ù½Ã ÀÔ·Â => ";
			cin >> attendanceSymbol;
		}

		AttendanceInformation[currentFilled - 1].atten_Symbol[index++] = attendanceSymbol;

		temp = temp->next;
	}

	AttendanceFormInput();
}

/*Ãâ¼® Á¤º¸ Ãâ·Â Æû*/
void AttendanceClass::AttendancePrintForm() {
	int index = 0;

	int placetype;

	system("cls");

	if (!currentFilled) { // Àå¼Ò µ¥ÀÌÅÍ°¡ ¾ø´Ù¸é
		return isEmpty();
	}

	while (index < currentFilled) // Àå¼Ò µ¥ÀÌÅÍ°¹¼ö ¸¸Å­
	{
		cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
		cout << " ³¯Â¥ " << GetPeopleDates[index].year << "³â " << GetPeopleDates[index].month << "¿ù " << GetPeopleDates[index].day << "ÀÏ " << endl;
		cout << " " << index + 1 << ". " << AttendanceInformation[index].PlaceName << endl;
		cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl << endl;

		index++;
	}

	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢=> ¾îµð Àå¼Ò°¡ ±Ã±Ý ÇÏ¼¼¿ä?           ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
	cout << " => ";
	cin >> placetype;

	cout << endl;

	while (!(placetype >= 1 && placetype <= currentFilled)) {
		cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
		cout << "¦¢=> Àß¸øÀÔ·ÂÇÏ¼Ì½À´Ï´Ù.                ¦¢" << endl;
		cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
		cout << " ´Ù½Ã ÀÔ·Â => ";
		cin >> placetype;
	}

	AttendancePrint(placetype);
}

/*Ãâ¼® Á¤º¸ Ãâ·Â*/
void AttendanceClass::AttendancePrint(int placetype) {
	int index = 0;
	Node* temp = peopleList->head;

	bool replay;

	system("cls");

	while (temp->next != peopleList->tail) { // µ¥ÀÌÅÍ°¡ ¾øÀ» ¶§ ±îÁö
		string currentAT_Type;
		currentAT_Type.clear();

		if (!AttendanceInformation[placetype - 1].atten_Symbol[index].compare("O")) {
			currentAT_Type = "Ãâ¼®";
		}
		else if (!AttendanceInformation[placetype - 1].atten_Symbol[index].compare("/")) {
			currentAT_Type = "Áö°¢";
			temp->next->peopleData.haveCost -= 2000;
		}
		else if(!AttendanceInformation[placetype - 1].atten_Symbol[index].compare("X")){
			currentAT_Type = "°á¼®";
			temp->next->peopleData.haveCost -= 2000;
		}
		cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
		cout << "¦¢ÀÌ¸§ : " << temp->next->peopleData.name << " Ãâ¼® ¿©ºÎ : " << currentAT_Type << "        ¦¢" << endl;
		cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;

		index++;

		temp = temp->next;
	}

	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢1. ´Ù½Ã º¸±â                          ¦¢" << endl;
	cout << "¦¢0. µÚ·Î °¡±â                          ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
	cout << " => ";
	cin >> replay;

	if (replay) AttendancePrint(placetype);
	else AttendanceFormInput();

}

/*³¯Â¥ ÀÔ·Â Á¶°Ç °Ë»ç*/
void AttendanceClass::IfDateEnterSet(Dates date) {
	if ((date.year % 4 == 0 && date.year % 100 != 0 || date.year % 400 == 0)) { // À±³âÀÏ ¶§
		if ((date.month >= 1 && date.month < 13)) {
			if (date.month != 2) { // 2¿ùÀÌ ¾Æ´Ñ ´Þ
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
			else { // 2¿ù
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
	else { // À±³âÀÌ ¾Æ´Ò ¶§
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

/*¿¡·¯ ÀÌº¥Æ®*/
void AttendanceClass::ErrorEvent() {
	system("cls");
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢=> ³¯Â¥¸¦ Àß¸øÀÔ·ÂÇß½À´Ï´Ù.           ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
	Sleep(3000);
}

/*³¯Â¥ µ¥ÀÌÅÍ ¼¼ÆÃ*/
void AttendanceClass::DateSetting(Dates date) { 
	_dates = date;

	for (int i = 0; i < MAX_ATTENDANCE_NUMBER; i++) {
		if (GetPeopleDates[i].year == NULL) { // ºñ¾îÀÖ´Â °÷ºÎÅÍ ³Ö¾îÁÜ
			GetPeopleDates[i] = _dates;
			return;
		}
	}
}

/*Àå¼Ò µ¥ÀÌÅÍ ¼¼ÆÃ*/
void AttendanceClass::PlaceSetting(string Pname) {
	_placeName = Pname;

	for (int i = 0; i < MAX_ATTENDANCE_NUMBER; i++) {
		if (AttendanceInformation[i].PlaceName.empty()) { // ºñ¾îÀÖ´Â °÷ ºÎÅÍ ³Ö¾îÁÜ
			PlaceName[i] = _placeName;
			AttendanceInformation[i].PlaceName = _placeName;
			currentFilled++; // Àå¼Ò °¹¼ö Áõ°¡

			return;
		}
	}
}

#pragma region InitSetting

/*ÃÊ±â µ¥ÀÌÅÍ ÇÒ´ç Å¬·¡½º*/
class InitSetting
{
public:
	InitSetting();
};

/*ÃÊ±â µ¥ÀÌÅÍ ÇÒ´ç »ý¼ºÀÚ*/
InitSetting::InitSetting()
{
	for (int i = 0; i < MAX_PEOPLE_NUMBER; i++) {
		peopleList->endInsert(EarlyData[i]); // ÃÊ±âµ¥ÀÌÅÍ »ðÀÔ
	}
	for (int i = 0; i < MAX_ATTENDANCE_NUMBER; i++) {
		AttendanceInformation[i].PlaceName.clear(); // Àå¼Ò µ¥ÀÌÅÍ Å¬¸°
	}
}

#pragma endregion

/* MainºÎºÐ */
int main()
{
	InitSetting Initmachine; // ÃÊ±â µ¥ÀÌÅÍ »ý¼º

	int jobTypeNumber;

	while (true) // ¹«ÇÑ·çÇÁ
	{
		InputForm();

		cout << "¿øÇÏ½Ã´Â ÀÛ¾÷À» ÀÔ·ÂÇÏ¼¼¿ä : ";
		cin >> jobTypeNumber;
		cout << endl;

		OutputForm(jobTypeNumber);
	}
	return 0;
}

/* InputForm ºÎºÐ */
void InputForm() {
	system("cls");
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢                                      ¦¢" << endl;
	cout << "¦¢      < Game Makers Ãâ¼®°ü¸® >        ¦¢" << endl;
	cout << "¦¢                                      ¦¢" << endl;
	cout << "¦¢1. È¸¿ø Á¤º¸ ÀÔ·Â                     ¦¢" << endl;
	cout << "¦¢2. È¸¿ø Á¤º¸ Ãâ·Â                     ¦¢" << endl;
	cout << "¦¢3. È¸¿ø Á¤º¸ »èÁ¦                     ¦¢" << endl;
	cout << "¦¢4. Áö°¢ºñ °ü·Ã                        ¦¢" << endl;
	cout << "¦¢5. Ãâ¼®Á¤º¸ °ü·Ã                      ¦¢" << endl;
	cout << "¦¢0. ÇÁ·Î±×·¥ Á¾·á                      ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
}

/* Output ºÎºÐ */
void OutputForm(int numberType) {
	AttendanceClass Attenmachine;

	switch (numberType)
	{
	case 0:
		cout << "ÇÁ·Î±×·¥À» Á¾·áÇÏ°Ú½À´Ï´Ù." << endl;
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
			cout << "Àß¸øµÈ °ªÀ» ÀÔ·ÂÇÏ¼Ì½À´Ï´Ù." << endl;
			cout << "´Ù½Ã ÀÔ·ÂÇÏ¼¼¿ä : ";
			cin >> numberType;
			cout << endl;
		}
		OutputForm(numberType);
		break;
	}
}

/* µ¥ÀÌÅÍ »ðÀÔºÎºÐ (º¸¿Ï)*/
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
			cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
			cout << "¦¢µ¥ÀÌÅÍ°¡ ²Ê¾Ç Ã¡½À´Ï´Ù.               ¦¢" << endl;
			cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
			Sleep(2000);

			return;
		}

	}

	if (peopleList->head->next == peopleList->tail) {
		isEmpty();
	}

	for (int i = currentDataPeoples; i < MAX_PEOPLE_NUMBER; i++) {
		
		cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
		 printf("¦¢=> %2d¹ø Â° µ¥ÀÌÅÍ ÀÔ·Â                ¦¢\n", i + 1);
		cout << "¦¢=> ÀÌ¸§ - ³ªÀÌ - Á÷¹« ¼ø              ¦¢" << endl;
		cout << "¦¢=> °³¹ß : 1 / µðÀÚÀÎ : 2 / ±âÈ¹ : 3   ¦¢" << endl;
		cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;

		cout << "ÀÌ¸§ : ";
		cin >> E_name;
		currentPeople.name = E_name;

		cout << "³ªÀÌ : ";
		cin >> E_age;
		currentPeople.age = E_age;

		cout << "Á÷¹« : ";
		cin >> E_dept;

		while (!(E_dept > 0 && E_dept < 4)) {
			cout << "Á÷¹«¸¦ Àß¸øÀÔ·ÂÇÏ¼Ì½À´Ï´Ù." << endl;
			cout << "Á÷¹« ´Ù½ÃÀÔ·Â : ";
			cin >> E_dept;
		}

		currentPeople.department = E_dept;
		currentPeople.haveCost = 20000;

		peopleList->endInsert(currentPeople);
	}
}

/* µ¥ÀÌÅÍ Ãâ·ÂºÎºÐ*/
void PrintData() {
	string currentDept;
	bool replay;

	Node* temp = peopleList->head;

	if (peopleList->head->next == peopleList->tail) { // µ¥ÀÌÅÍ°¡ ¾ÆÁ÷ µé¾î°¬Áö ¾Ê¾Ò´Ù¸é
		return isEmpty();
	}

	system("cls");
	while (temp->next != peopleList->tail) { // ´ÙÀ½ µ¥ÀÌÅÍ°¡ ¾øÀ» ¶§ ±îÁö

		if (temp->next->peopleData.department == TYPE_DEVELOPER + 1) {
			currentDept = "°³¹ß";
		}
		else if (temp->next->peopleData.department == TYPE_DESIGNER + 1) {
			currentDept = "±×¸²";
		}
		else {
			currentDept = "±âÈ¹";
		}
		cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
		cout << "¦¢ÀÌ¸§ : " << temp->next->peopleData.name << "                         ¦¢" << endl;
		 printf("¦¢³ªÀÌ : %2d »ì                          ¦¢\n", temp->next->peopleData.age);
		cout << "¦¢Á÷¹« : " << currentDept << "                           ¦¢" << endl;
		cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;

		temp = temp->next;
	}

	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢1. ´Ù½Ã º¸±â                          ¦¢" << endl;
	cout << "¦¢0. µÚ·Î °¡±â                          ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
	cout << " => ";
	cin >> replay;

	if (replay) PrintData();
	else return;
}

/*Æ¯Á¤ µ¥ÀÌÅÍ »èÁ¦ºÎºÐ*/
void DeleteData() {
	system("cls");

	string findName;

	string currentSymbol;

	Node* temp = peopleList->head;

	int count = 0;

	if (peopleList->head->next == peopleList->tail) { // µ¥ÀÌÅÍ°¡ ¾ÆÁ÷ µé¾î°¬Áö ¾Ê¾Ò´Ù¸é
		return isEmpty();
	}

	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢=> ´©±¼ »èÁ¦ ÇÒ ²«°¡¿ä?               ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
	cout << "ÀÌ¸§ => ";
	cin >> findName;

	while (temp->next != peopleList->tail) { // ´ÙÀ½ µ¥ÀÌÅÍ°¡ ¾øÀ» ¶§ ±îÁö

		temp = temp->next;

		if (!temp->peopleData.name.compare(findName)) {
			temp->selvDelete();

			currentDataPeoples--;

			for (int i = 0; i < MAX_ATTENDANCE_NUMBER; i++) { // »èÁ¦°¡ ÀÌ·ç¾î Áö¸é Ãâ¼®µµ »èÁ¦
				for (int j = count; j < MAX_ATTENDANCE_NUMBER; j++) {
					AttendanceInformation[i].atten_Symbol[j] = AttendanceInformation[i].atten_Symbol[j + 1];
				}
			}

			cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
			cout << "¦¢=> »èÁ¦ µÇ¾ú½À´Ï´Ù.                   ¦¢" << endl;
			cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;

			Sleep(2000);

			return;
		}

		count++;
	}

	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢=> ÇØ´ç ÀÌ¸§ÀÌ ¾ø½À´Ï´Ù.              ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;

	Sleep(2000);

}

/*Áö°¢ºñ Ã³¸® Æû ºÎºÐ*/
void CostEnterForm() {
	int jobType;

	if (peopleList->head->next == peopleList->tail) {
		return isEmpty();
	}

	system("cls");

	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢1. Áö°¢ºñ Á¤º¸ Ãâ·Â                   ¦¢" << endl;
	cout << "¦¢2. Áö°¢ºñ »èÁ¦                        ¦¢" << endl;
	cout << "¦¢0. µÚ·Î°¡±â                           ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
	cout << " => ";
	cin >> jobType;

	CostEnterData(jobType);
}

/*Áö°¢ºñ Ã³¸® µ¥ÀÌÅÍ ºÎºÐ */
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

			cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
			cout << "¦¢ÀÌ¸§ : " << temp->next->peopleData.name << "                         ¦¢" << endl;
			printf("¦¢³²Àº Áö°¢ºñ : %5d ¿ø                ¦¢\n", temp->next->peopleData.haveCost);
			cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;

			temp = temp->next;
		}

		cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
		cout << "¦¢1. ´Ù½Ã º¸±â                          ¦¢" << endl;
		cout << "¦¢0. µÚ·Î °¡±â                          ¦¢" << endl;
		cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
		cout << " => ";
		cin >> replay;

		if (replay) CostEnterData(jobType);
		else return CostEnterForm();

		break;

	case 2:
		cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
		cout << "¦¢=> ´©±¼ Â÷°¨ ÇÒ ²«°¡¿ä?               ¦¢" << endl;
		cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
		cout << "ÀÌ¸§ => ";
		cin >> findName;

		temp = peopleList->head;

		do {
			temp = temp->next;

			if (!temp->peopleData.name.compare(findName)) {
				temp->peopleData.haveCost -= 2000;

				cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
				cout << "¦¢=> Â÷°¨ µÇ¾ú½À´Ï´Ù.                   ¦¢" << endl;
				cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;

				Sleep(2000);

				return CostEnterForm();
			}

		} while (temp->next != peopleList->tail);


		cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
		cout << "¦¢=> ÇØ´ç ÀÌ¸§ÀÌ ¾ø½À´Ï´Ù.              ¦¢" << endl;
		cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;

		Sleep(2000);

		CostEnterForm();

		break;

	default:
		while (!(jobType >= 0 && jobType <= 2)) {
			cout << "Àß¸øµÈ °ªÀ» ÀÔ·ÂÇÏ¼Ì½À´Ï´Ù." << endl;
			cout << "´Ù½Ã ÀÔ·ÂÇÏ¼¼¿ä : ";
			cin >> jobType;
		}
		break;
	}

}

/*°ø¹é ÀÌº¥Æ® Ã³¸® ºÎºÐ*/
void isEmpty() {
	system("cls");
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢¾ÆÁ÷ µ¥ÀÌÅÍ°¡ ¾ø½À´Ï´Ù.               ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl << endl;
	Sleep(2000);
}
