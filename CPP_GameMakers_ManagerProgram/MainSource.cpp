#include <iostream>
#include <cstring>
#include <string>
#include <windows.h>
#include <fstream>
#include "DoubleLinkedListSource.h" // ���߿��� ����Ʈ ����
#include "AttendanceInteraction.h" // �⼮ ����

using namespace std;

/*���� ����*/
enum DepartmentType {
	TYPE_DEVELOPER, // ����
	TYPE_DESIGNER, // �����̳�
	TYPE_PLANNER // ��ȹ��
};

#pragma region Methods

/*Form��*/
void InputForm(); // �Է� ��
void OutputForm(int x); // �ƿ� ó�� ��
void CostEnterForm(); // ������ �Է���
void isEmpty(); // �� ���� �̺�Ʈ

/*�Լ���*/
void EnterData(); // ������ �Է�
void PrintData(); // ������ ���
void DeleteData(); // ������ ����
void CostEnterData(int x); // ������ �Է�

#pragma endregion

/*��¥ ���� Ŭ����*/
class DateClass
{
protected:
	Dates _dates;

public:
	virtual void DateSetting(Dates date) = 0;
	virtual void IfDateEnterSet(Dates date) = 0;
	virtual void ErrorEvent() = 0;
};

/*��� ���� Ŭ����*/
class PlaceClass
{
protected:
	string _placeName;

public:
	virtual void PlaceSetting(string Pname) = 0;
};

/*�⼮���� Ŭ����*/
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

/*�⼮ �޴� ��*/
void AttendanceClass::AttendanceFormInput() {
	int jobType;

	system("cls");
	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "��1. �⼮ �Է�                          ��" << endl;
	cout << "��2. �⼮ ��ȸ                          ��" << endl;
	cout << "��0. �ڷ� ����                          ��" << endl;
	cout << "��������������������������������������������������������������������������������" << endl;
	cout << " => ";
	cin >> jobType;

	AttendanceFormOutput(jobType);
}

/*�⼮ �޴� �ƿ� ��*/
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
			cout << "�߸��� ���� �Է��ϼ̽��ϴ�." << endl;
			cout << "�ٽ� �Է��ϼ��� : ";
			cin >> type;
			cout << endl;
		}
		AttendanceFormOutput(type);

		break;
	}
}

/*�⼮ ���� �Է�*/
void AttendanceClass::AttendanceEnter() {
	Dates current_Date;
	string currentPlaceName;
	string attendanceSymbol;

	int index = 0;

	Node* temp = peopleList->head;

	system("cls");

	if (peopleList->head->next == peopleList->tail) { // �����Ͱ� ���ٸ�
		return isEmpty();
	}

	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "��=> ��¥ �Է�                          ��" << endl;
	cout << "��=> (�⵵ - �� - �� ������)            ��" << endl;
	cout << "��������������������������������������������������������������������������������" << endl;
	cout << " => ";
	cin >> current_Date.year;
	cin >> current_Date.month;
	cin >> current_Date.day;

	IfDateEnterSet(current_Date);
	DateSetting(current_Date);

	cin.ignore();

	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "��=> ��� �Է�                          ��" << endl;
	cout << "��������������������������������������������������������������������������������" << endl;
	cout << " => ";
	getline(cin, currentPlaceName);

	PlaceSetting(currentPlaceName);

	system("cls");

	cout << "������������������������������������������������������������������������������" << endl;
	cout << "=> "<< current_Date.year << " �� " << current_Date.month << " �� " << current_Date.day << " ��" << "" << endl;
	cout << "=> ��� " << currentPlaceName << endl;
	cout << "=> (O �⼮ / ���� X �Ἦ)              " << endl;
	cout << "������������������������������������������������������������������������������" << endl;

	while (temp->next != peopleList->tail) { // ���� �����Ͱ� ���� �� ����

		cout << "��������������������������������������������������������������������������������" << endl;
		cout << "���̸� : " << temp->next->peopleData.name << "                         ��" << endl;
		cout << "��������������������������������������������������������������������������������" << endl;
		cout << " => ";
		cin >> attendanceSymbol;

		cout << endl;

		while (!(attendanceSymbol == "O" || attendanceSymbol == "/" || attendanceSymbol == "X")) {
			cout << "��������������������������������������������������������������������������������" << endl;
			cout << "��=> ��ȣ�� �߸��Է��߽��ϴ�.           ��" << endl;
			cout << "��������������������������������������������������������������������������������" << endl;
			cout << " �ٽ� �Է� => ";
			cin >> attendanceSymbol;
		}

		AttendanceInformation[currentFilled - 1].atten_Symbol[index++] = attendanceSymbol;

		temp = temp->next;
	}

	AttendanceFormInput();
}

/*�⼮ ���� ��� ��*/
void AttendanceClass::AttendancePrintForm() {
	int index = 0;

	int placetype;

	system("cls");

	if (!currentFilled) { // ��� �����Ͱ� ���ٸ�
		return isEmpty();
	}

	while (index < currentFilled) // ��� �����Ͱ��� ��ŭ
	{
		cout << "��������������������������������������������������������������������������������" << endl;
		cout << " ��¥ " << GetPeopleDates[index].year << "�� " << GetPeopleDates[index].month << "�� " << GetPeopleDates[index].day << "�� " << endl;
		cout << " " << index + 1 << ". " << AttendanceInformation[index].PlaceName << endl;
		cout << "��������������������������������������������������������������������������������" << endl << endl;

		index++;
	}

	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "��=> ��� ��Ұ� �ñ� �ϼ���?           ��" << endl;
	cout << "��������������������������������������������������������������������������������" << endl;
	cout << " => ";
	cin >> placetype;

	cout << endl;

	while (!(placetype >= 1 && placetype <= currentFilled)) {
		cout << "��������������������������������������������������������������������������������" << endl;
		cout << "��=> �߸��Է��ϼ̽��ϴ�.                ��" << endl;
		cout << "��������������������������������������������������������������������������������" << endl;
		cout << " �ٽ� �Է� => ";
		cin >> placetype;
	}

	AttendancePrint(placetype);
}

/*�⼮ ���� ���*/
void AttendanceClass::AttendancePrint(int placetype) {
	int index = 0;
	Node* temp = peopleList->head;

	bool replay;

	system("cls");

	while (temp->next != peopleList->tail) { // �����Ͱ� ���� �� ����
		string currentAT_Type;
		currentAT_Type.clear();

		if (!AttendanceInformation[placetype - 1].atten_Symbol[index].compare("O")) {
			currentAT_Type = "�⼮";
		}
		else if (!AttendanceInformation[placetype - 1].atten_Symbol[index].compare("/")) {
			currentAT_Type = "����";
			temp->next->peopleData.haveCost -= 2000;
		}
		else if(!AttendanceInformation[placetype - 1].atten_Symbol[index].compare("X")){
			currentAT_Type = "�Ἦ";
			temp->next->peopleData.haveCost -= 2000;
		}
		cout << "��������������������������������������������������������������������������������" << endl;
		cout << "���̸� : " << temp->next->peopleData.name << " �⼮ ���� : " << currentAT_Type << "        ��" << endl;
		cout << "��������������������������������������������������������������������������������" << endl;

		index++;

		temp = temp->next;
	}

	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "��1. �ٽ� ����                          ��" << endl;
	cout << "��0. �ڷ� ����                          ��" << endl;
	cout << "��������������������������������������������������������������������������������" << endl;
	cout << " => ";
	cin >> replay;

	if (replay) AttendancePrint(placetype);
	else AttendanceFormInput();

}

/*��¥ �Է� ���� �˻�*/
void AttendanceClass::IfDateEnterSet(Dates date) {
	if ((date.year % 4 == 0 && date.year % 100 != 0 || date.year % 400 == 0)) { // ������ ��
		if ((date.month >= 1 && date.month < 13)) {
			if (date.month != 2) { // 2���� �ƴ� ��
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
			else { // 2��
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
	else { // ������ �ƴ� ��
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

/*���� �̺�Ʈ*/
void AttendanceClass::ErrorEvent() {
	system("cls");
	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "��=> ��¥�� �߸��Է��߽��ϴ�.           ��" << endl;
	cout << "��������������������������������������������������������������������������������" << endl;
	Sleep(3000);
}

/*��¥ ������ ����*/
void AttendanceClass::DateSetting(Dates date) { 
	_dates = date;

	for (int i = 0; i < MAX_ATTENDANCE_NUMBER; i++) {
		if (GetPeopleDates[i].year == NULL) { // ����ִ� ������ �־���
			GetPeopleDates[i] = _dates;
			return;
		}
	}
}

/*��� ������ ����*/
void AttendanceClass::PlaceSetting(string Pname) {
	_placeName = Pname;

	for (int i = 0; i < MAX_ATTENDANCE_NUMBER; i++) {
		if (AttendanceInformation[i].PlaceName.empty()) { // ����ִ� �� ���� �־���
			PlaceName[i] = _placeName;
			AttendanceInformation[i].PlaceName = _placeName;
			currentFilled++; // ��� ���� ����

			return;
		}
	}
}

#pragma region InitSetting

/*�ʱ� ������ �Ҵ� Ŭ����*/
class InitSetting
{
public:
	InitSetting();
};

/*�ʱ� ������ �Ҵ� ������*/
InitSetting::InitSetting()
{
	for (int i = 0; i < MAX_PEOPLE_NUMBER; i++) {
		peopleList->endInsert(EarlyData[i]); // �ʱⵥ���� ����
	}
	for (int i = 0; i < MAX_ATTENDANCE_NUMBER; i++) {
		AttendanceInformation[i].PlaceName.clear(); // ��� ������ Ŭ��
	}
}

#pragma endregion

/* Main�κ� */
int main()
{
	InitSetting Initmachine; // �ʱ� ������ ����

	int jobTypeNumber;

	while (true) // ���ѷ���
	{
		InputForm();

		cout << "���Ͻô� �۾��� �Է��ϼ��� : ";
		cin >> jobTypeNumber;
		cout << endl;

		OutputForm(jobTypeNumber);
	}
	return 0;
}

/* InputForm �κ� */
void InputForm() {
	system("cls");
	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "��                                      ��" << endl;
	cout << "��      < Game Makers �⼮���� >        ��" << endl;
	cout << "��                                      ��" << endl;
	cout << "��1. ȸ�� ���� �Է�                     ��" << endl;
	cout << "��2. ȸ�� ���� ���                     ��" << endl;
	cout << "��3. ȸ�� ���� ����                     ��" << endl;
	cout << "��4. ������ ����                        ��" << endl;
	cout << "��5. �⼮���� ����                      ��" << endl;
	cout << "��0. ���α׷� ����                      ��" << endl;
	cout << "��������������������������������������������������������������������������������" << endl;
}

/* Output �κ� */
void OutputForm(int numberType) {
	AttendanceClass Attenmachine;

	switch (numberType)
	{
	case 0:
		cout << "���α׷��� �����ϰڽ��ϴ�." << endl;
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
			cout << "�߸��� ���� �Է��ϼ̽��ϴ�." << endl;
			cout << "�ٽ� �Է��ϼ��� : ";
			cin >> numberType;
			cout << endl;
		}
		OutputForm(numberType);
		break;
	}
}

/* ������ ���Ժκ� (����)*/
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
			cout << "��������������������������������������������������������������������������������" << endl;
			cout << "�������Ͱ� �ʾ� á���ϴ�.               ��" << endl;
			cout << "��������������������������������������������������������������������������������" << endl;
			Sleep(2000);

			return;
		}

	}

	if (peopleList->head->next == peopleList->tail) {
		isEmpty();
	}

	for (int i = currentDataPeoples; i < MAX_PEOPLE_NUMBER; i++) {
		
		cout << "��������������������������������������������������������������������������������" << endl;
		 printf("��=> %2d�� ° ������ �Է�                ��\n", i + 1);
		cout << "��=> �̸� - ���� - ���� ��              ��" << endl;
		cout << "��=> ���� : 1 / ������ : 2 / ��ȹ : 3   ��" << endl;
		cout << "��������������������������������������������������������������������������������" << endl;

		cout << "�̸� : ";
		cin >> E_name;
		currentPeople.name = E_name;

		cout << "���� : ";
		cin >> E_age;
		currentPeople.age = E_age;

		cout << "���� : ";
		cin >> E_dept;

		while (!(E_dept > 0 && E_dept < 4)) {
			cout << "������ �߸��Է��ϼ̽��ϴ�." << endl;
			cout << "���� �ٽ��Է� : ";
			cin >> E_dept;
		}

		currentPeople.department = E_dept;
		currentPeople.haveCost = 20000;

		peopleList->endInsert(currentPeople);
	}
}

/* ������ ��ºκ�*/
void PrintData() {
	string currentDept;
	bool replay;

	Node* temp = peopleList->head;

	if (peopleList->head->next == peopleList->tail) { // �����Ͱ� ���� ���� �ʾҴٸ�
		return isEmpty();
	}

	system("cls");
	while (temp->next != peopleList->tail) { // ���� �����Ͱ� ���� �� ����

		if (temp->next->peopleData.department == TYPE_DEVELOPER + 1) {
			currentDept = "����";
		}
		else if (temp->next->peopleData.department == TYPE_DESIGNER + 1) {
			currentDept = "�׸�";
		}
		else {
			currentDept = "��ȹ";
		}
		cout << "��������������������������������������������������������������������������������" << endl;
		cout << "���̸� : " << temp->next->peopleData.name << "                         ��" << endl;
		 printf("������ : %2d ��                          ��\n", temp->next->peopleData.age);
		cout << "������ : " << currentDept << "                           ��" << endl;
		cout << "��������������������������������������������������������������������������������" << endl;

		temp = temp->next;
	}

	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "��1. �ٽ� ����                          ��" << endl;
	cout << "��0. �ڷ� ����                          ��" << endl;
	cout << "��������������������������������������������������������������������������������" << endl;
	cout << " => ";
	cin >> replay;

	if (replay) PrintData();
	else return;
}

/*Ư�� ������ �����κ�*/
void DeleteData() {
	system("cls");

	string findName;

	string currentSymbol;

	Node* temp = peopleList->head;

	int count = 0;

	if (peopleList->head->next == peopleList->tail) { // �����Ͱ� ���� ���� �ʾҴٸ�
		return isEmpty();
	}

	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "��=> ���� ���� �� ������?               ��" << endl;
	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "�̸� => ";
	cin >> findName;

	while (temp->next != peopleList->tail) { // ���� �����Ͱ� ���� �� ����

		temp = temp->next;

		if (!temp->peopleData.name.compare(findName)) {
			temp->selvDelete();

			currentDataPeoples--;

			for (int i = 0; i < MAX_ATTENDANCE_NUMBER; i++) { // ������ �̷�� ���� �⼮�� ����
				for (int j = count; j < MAX_ATTENDANCE_NUMBER; j++) {
					AttendanceInformation[i].atten_Symbol[j] = AttendanceInformation[i].atten_Symbol[j + 1];
				}
			}

			cout << "��������������������������������������������������������������������������������" << endl;
			cout << "��=> ���� �Ǿ����ϴ�.                   ��" << endl;
			cout << "��������������������������������������������������������������������������������" << endl;

			Sleep(2000);

			return;
		}

		count++;
	}

	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "��=> �ش� �̸��� �����ϴ�.              ��" << endl;
	cout << "��������������������������������������������������������������������������������" << endl;

	Sleep(2000);

}

/*������ ó�� �� �κ�*/
void CostEnterForm() {
	int jobType;

	if (peopleList->head->next == peopleList->tail) {
		return isEmpty();
	}

	system("cls");

	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "��1. ������ ���� ���                   ��" << endl;
	cout << "��2. ������ ����                        ��" << endl;
	cout << "��0. �ڷΰ���                           ��" << endl;
	cout << "��������������������������������������������������������������������������������" << endl;
	cout << " => ";
	cin >> jobType;

	CostEnterData(jobType);
}

/*������ ó�� ������ �κ� */
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

			cout << "��������������������������������������������������������������������������������" << endl;
			cout << "���̸� : " << temp->next->peopleData.name << "                         ��" << endl;
			printf("������ ������ : %5d ��                ��\n", temp->next->peopleData.haveCost);
			cout << "��������������������������������������������������������������������������������" << endl;

			temp = temp->next;
		}

		cout << "��������������������������������������������������������������������������������" << endl;
		cout << "��1. �ٽ� ����                          ��" << endl;
		cout << "��0. �ڷ� ����                          ��" << endl;
		cout << "��������������������������������������������������������������������������������" << endl;
		cout << " => ";
		cin >> replay;

		if (replay) CostEnterData(jobType);
		else return CostEnterForm();

		break;

	case 2:
		cout << "��������������������������������������������������������������������������������" << endl;
		cout << "��=> ���� ���� �� ������?               ��" << endl;
		cout << "��������������������������������������������������������������������������������" << endl;
		cout << "�̸� => ";
		cin >> findName;

		temp = peopleList->head;

		do {
			temp = temp->next;

			if (!temp->peopleData.name.compare(findName)) {
				temp->peopleData.haveCost -= 2000;

				cout << "��������������������������������������������������������������������������������" << endl;
				cout << "��=> ���� �Ǿ����ϴ�.                   ��" << endl;
				cout << "��������������������������������������������������������������������������������" << endl;

				Sleep(2000);

				return CostEnterForm();
			}

		} while (temp->next != peopleList->tail);


		cout << "��������������������������������������������������������������������������������" << endl;
		cout << "��=> �ش� �̸��� �����ϴ�.              ��" << endl;
		cout << "��������������������������������������������������������������������������������" << endl;

		Sleep(2000);

		CostEnterForm();

		break;

	default:
		while (!(jobType >= 0 && jobType <= 2)) {
			cout << "�߸��� ���� �Է��ϼ̽��ϴ�." << endl;
			cout << "�ٽ� �Է��ϼ��� : ";
			cin >> jobType;
		}
		break;
	}

}

/*���� �̺�Ʈ ó�� �κ�*/
void isEmpty() {
	system("cls");
	cout << "��������������������������������������������������������������������������������" << endl;
	cout << "������ �����Ͱ� �����ϴ�.               ��" << endl;
	cout << "��������������������������������������������������������������������������������" << endl << endl;
	Sleep(2000);
}
