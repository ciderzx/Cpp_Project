using namespace std;

/*최대 사람 정보*/
#define MAX_PEOPLE_NUMBER 21

/*사람 정보*/
typedef struct Profile {
	string name; // 이름
	int age; // 나이
	int department; // 직무
	int haveCost; // 지각비용
}Profile;

/*데이터 갯수*/
typedef int peopleDataNumber;

/*데이터 노드*/
struct Node {
	Profile peopleData;  // 노드 데이터
	Node* next, *prev; // 다음주소와 이전 주소

	Node() { // 생성자
		next = prev = NULL;
		peopleData.age = NULL;
		peopleData.name = "";
		peopleData.department = NULL;
	}

	Node(Profile people, Node* ptr)//ptr 뒤에 추가한다.
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

/*이중연결 리스트*/
struct DLinkedList {
	Node *head; // 위에 주소
	Node *tail; // 다음 주소
	int count;

	DLinkedList() { //생성자
		count = 0;
		head = new Node(); //더미를 선언해서 가지고 있게한다
		tail = new Node(); //더미를 선언해서 가지고 있게한다
		head->next = tail; //서로연결한다.
		tail->prev = head;
	}

	~DLinkedList() { // 프로그램이 끝나면 메모리 해제
		while (head->next != tail)
			head->next->selvDelete();

		delete head;
		delete tail;
	}

	void firstInsert(Profile people) { //head 다음에 추가한다.
		new Node(people, head);
	}

	void endInsert(Profile people) { //tail 앞에 추가한다.
		new Node(people, tail->prev);
	}
};

/*초기 데이터 정보*/
Profile EarlyData[MAX_PEOPLE_NUMBER] = { // 이름 나이 직무 지각비용으로 이루어져있음
	{"전형근", 27, 1, 20000},
	{"홍진수", 26, 1, 20000},
	{"남태현", 25, 1, 20000},
	{"문지은", 23, 1, 20000},
	{"이해인", 26, 2, 20000},
	{"박승우", 20, 1, 20000},
	{"김수빈", 21, 3, 20000},
	{"이호연", 24, 1, 20000},
	{"박성민", 25, 3, 20000},
	{"김우현", 24, 3, 20000},
	{"정원영", 30, 3, 20000},
	{"최수민", 23, 2, 20000},
	{"박재성", 22, 1, 20000},
	{"윤성현", 22, 1, 20000},
	{"이강우", 24, 1, 20000},
	{"장정인", 23, 1, 20000},
	{"김영우", 26, 1, 20000},
	{"황우진", 24, 1, 20000},
	{"전영태", 26, 1, 20000},
	{"권희정", 23, 2, 20000},
	{"김보민", 22, 2, 20000}
};

/*데이터 부분*/
DLinkedList *peopleList = new DLinkedList();

/*현재 가지고 있는 갯수*/
peopleDataNumber currentDataPeoples = 0;