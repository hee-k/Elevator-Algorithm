#include <iostream>
#include <cstring>
#include <thread>
using namespace std;
using std::this_thread::sleep_for;

// People Class
class People {
public:
	int currentFloor = 1;		// �°����� ���� ��
	int count = 0;				// ž�� �ο�

	int getPeople();			// ���������� ž�� �޼ҵ�
};

int People::getPeople() {
	// ž�� �ο� �Է� (�ִ� 5��)
	do {
		cin >> count;
		// �ִ� ž�� ���� �ο�(5��) �ʰ� �� ���Է�
		if (count > 5) {
			cout << "\n�ִ� ž�� ���� �ο� �ʰ�! �ٽ� �Է����ּ��� : ";
		}
		// 0 or ���� �Է½� ���Է�
		else if (count <= 0) {
			cout << "\n�߸� �Է��ϼ̽��ϴ�! �ٽ� �Է����ּ��� : ";
		}
	} while (count > 5 || count <= 0);
	return count;
}

// Destination Class
class Destination {
private:
	int num1 = 0, num2 = 0, num3 = 0; // �ݺ����� ���̴� ����
protected:
	int index = 0;					  // ������ �迭�� indexȮ��
public:
	bool asc = true;				  // �������� ���

	void getDestination(int* destinaiton, int count);						 // ������ �Է� �޼ҵ�
	bool nearbyCurrentFloor(int* destination, int currentFloor, int count); // ���� ���� ���� ����� ������ ã��
};

void Destination::getDestination(int* destination, int count) {
	// ž�� �ο���ŭ ������ �� �Է�
	for (num1 = 1; num1 <= count; num1++) {
		cin >> destination[num1];
	}

	// ������ ���� ������������ ���� 
	for (num1 = 1; num1 < count; num1++) {
		for (num2 = 2; num2 <= count - num1 + 1; num2++) {
			if (destination[num2 - 1] > destination[num2]) {
				num3 = destination[num2 - 1];
				destination[num2 - 1] = destination[num2];
				destination[num2] = num3;
			}
		}
	}
}

bool Destination::nearbyCurrentFloor(int* destination, int currentFloor, int count) {
	// ������ �� ��, ���� ������ ����� ���� Ȯ��(�ش� ���� �迭�� index Ȯ��)
	if (abs(destination[1] - currentFloor) <= abs(destination[count] - currentFloor)) {
		index = 0;
		return true;
	}
	else {
		index = count + 1;
		return false;
	}
}

// Arrival Class
class Arrival : public Destination {
public:
	int arrive(int* destination, bool asc, int count);	 // ������ ���� �޼ҵ�
};

int Arrival::arrive(int* destination, bool asc, int count) {
	int currentFloor = 0;
	while (count >= 1) {
		// ���� ������ ����� �������� �̵�
		currentFloor = (asc == true) ? destination[++index] : destination[--index];
		// ������ ������ �� ���
		sleep_for(2000ms);
		cout << "\n" << currentFloor << "���� �����߽��ϴ�.\n";
		count--;
	}
	return currentFloor;
}

int main() {
	char run = 'y';	// �°��� ���� ����
	People ele;
	Arrival dest;

	// �°����� ���� ���� 1��
	ele.currentFloor = 1;
	while (run == 'y') {
		// ž�� �ο� �Է�
		cout << "\n���� �°��� ��ġ�� " << ele.currentFloor << "���Դϴ�.\n\nž�� �ο��� �Է��ϼ���(�ִ� 5��) : ";
		ele.count = ele.getPeople();

		// �ο�����ŭ ���� �Ҵ�
		int* destination = new int[ele.count + 1];
		if (!destination) {
			cout << "�޸𸮸� �Ҵ��� �� �����ϴ�.";
			return 0;
		}

		// ������ �� �Է�
		cout << "\n" << ele.count << "���� ������ ���� �Է��ϼ��� (�� �� �Է¸��� enter)\n";
		dest.getDestination(destination, ele.count);
		dest.asc = dest.nearbyCurrentFloor(destination, ele.currentFloor, ele.count);

		// ������ �� ����
		ele.currentFloor = dest.arrive(destination, dest.asc, ele.count);

		// �°��� ����� ����
		cout << "\n��� ������ ���� �����߽��ϴ�. �°��⸦ ����� �ұ��? (������Ϸ��� y�Է�) : ";
		cin >> run;
		cout << "\n================================================================================\n";

		//�޸� ����
		delete[] destination;
	}
	cout << "\n�°��� ������ �����մϴ�." << endl;
}