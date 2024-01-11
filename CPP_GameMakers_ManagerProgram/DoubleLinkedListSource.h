using namespace std;

/*�ִ� ��� ����*/
#define MAX_PEOPLE_NUMBER 21

/*��� ����*/
typedef struct Profile {
	string name; // �̸�
	int age; // ����
	int department; // ����
	int haveCost; // �������
}Profile;

/*������ ����*/
typedef int peopleDataNumber;

/*������ ���*/
struct Node {
	Profile peopleData;  // ��� ������
	Node* next, *prev; // �����ּҿ� ���� �ּ�

	Node() { // ������
		next = prev = NULL;
		peopleData.age = NULL;
		peopleData.name = "";
		peopleData.department = NULL;
	}

	Node(Profile people, Node* ptr)//ptr �ڿ� �߰��Ѵ�.
	{
		peopleData = people;
		prev = ptr;
		next = ptr->next;
		next->prev = prev->next = this;
	}

	void selvDelete() {
		prev->next = next;
		next->prev = prev;
		delete this;
	}
};

/*���߿��� ����Ʈ*/
struct DLinkedList {
	Node *head; // ���� �ּ�
	Node *tail; // ���� �ּ�
	int count;

	DLinkedList() { //������
		count = 0;
		head = new Node(); //���̸� �����ؼ� ������ �ְ��Ѵ�
		tail = new Node(); //���̸� �����ؼ� ������ �ְ��Ѵ�
		head->next = tail; //���ο����Ѵ�.
		tail->prev = head;
	}

	~DLinkedList() { // ���α׷��� ������ �޸� ����
		while (head->next != tail)
			head->next->selvDelete();

		delete head;
		delete tail;
	}

	void firstInsert(Profile people) { //head ������ �߰��Ѵ�.
		new Node(people, head);
	}

	void endInsert(Profile people) { //tail �տ� �߰��Ѵ�.
		new Node(people, tail->prev);
	}
};

/*�ʱ� ������ ����*/
Profile EarlyData[MAX_PEOPLE_NUMBER] = { // �̸� ���� ���� ����������� �̷��������
	{"������", 27, 1, 20000},
	{"ȫ����", 26, 1, 20000},
	{"������", 25, 1, 20000},
	{"������", 23, 1, 20000},
	{"������", 26, 2, 20000},
	{"�ڽ¿�", 20, 1, 20000},
	{"�����", 21, 3, 20000},
	{"��ȣ��", 24, 1, 20000},
	{"�ڼ���", 25, 3, 20000},
	{"�����", 24, 3, 20000},
	{"������", 30, 3, 20000},
	{"�ּ���", 23, 2, 20000},
	{"���缺", 22, 1, 20000},
	{"������", 22, 1, 20000},
	{"�̰���", 24, 1, 20000},
	{"������", 23, 1, 20000},
	{"�迵��", 26, 1, 20000},
	{"Ȳ����", 24, 1, 20000},
	{"������", 26, 1, 20000},
	{"������", 23, 2, 20000},
	{"�躸��", 22, 2, 20000}
};

/*������ �κ�*/
DLinkedList *peopleList = new DLinkedList();

/*���� ������ �ִ� ����*/
peopleDataNumber currentDataPeoples = 0;