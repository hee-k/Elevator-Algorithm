#include <iostream>
#include <cstring>
#include <thread>
using namespace std;
using std::this_thread::sleep_for;

// People Class
class People {
public:
	int currentFloor = 1;		// 승강기의 현재 층
	int count = 0;				// 탑승 인원

	int getPeople();			// 엘레베이터 탑승 메소드
};

int People::getPeople() {
	// 탑승 인원 입력 (최대 5명)
	do {
		cin >> count;
		// 최대 탑승 가능 인원(5명) 초과 시 재입력
		if (count > 5) {
			cout << "\n최대 탑승 가능 인원 초과! 다시 입력해주세요 : ";
		}
		// 0 or 음수 입력시 재입력
		else if (count <= 0) {
			cout << "\n잘못 입력하셨습니다! 다시 입력해주세요 : ";
		}
	} while (count > 5 || count <= 0);
	return count;
}

// Destination Class
class Destination {
private:
	int num1 = 0, num2 = 0, num3 = 0; // 반복문에 쓰이는 변수
protected:
	int index = 0;					  // 목적지 배열의 index확인
public:
	bool asc = true;				  // 오름차순 출력

	void getDestination(int* destinaiton, int count);						 // 목적지 입력 메소드
	bool nearbyCurrentFloor(int* destination, int currentFloor, int count); // 현재 층과 가장 가까운 목적지 찾기
};

void Destination::getDestination(int* destination, int count) {
	// 탑승 인원만큼 목적지 층 입력
	for (num1 = 1; num1 <= count; num1++) {
		cin >> destination[num1];
	}

	// 목적지 층을 오름차순으로 정렬 
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
	// 목적지 층 중, 현재 층에서 가까운 끝층 확인(해당 층의 배열의 index 확인)
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
	int arrive(int* destination, bool asc, int count);	 // 목적지 도착 메소드
};

int Arrival::arrive(int* destination, bool asc, int count) {
	int currentFloor = 0;
	while (count >= 1) {
		// 현재 층에서 가까운 끝층으로 이동
		currentFloor = (asc == true) ? destination[++index] : destination[--index];
		// 도착한 목적지 층 출력
		sleep_for(2000ms);
		cout << "\n" << currentFloor << "층에 도착했습니다.\n";
		count--;
	}
	return currentFloor;
}

int main() {
	char run = 'y';	// 승강기 운행 여부
	People ele;
	Arrival dest;

	// 승강기의 현재 층은 1층
	ele.currentFloor = 1;
	while (run == 'y') {
		// 탑승 인원 입력
		cout << "\n현재 승강기 위치는 " << ele.currentFloor << "층입니다.\n\n탑승 인원을 입력하세요(최대 5명) : ";
		ele.count = ele.getPeople();

		// 인원수만큼 동적 할당
		int* destination = new int[ele.count + 1];
		if (!destination) {
			cout << "메모리를 할당할 수 없습니다.";
			return 0;
		}

		// 목적지 층 입력
		cout << "\n" << ele.count << "개의 목적지 층을 입력하세요 (한 층 입력마다 enter)\n";
		dest.getDestination(destination, ele.count);
		dest.asc = dest.nearbyCurrentFloor(destination, ele.currentFloor, ele.count);

		// 목적지 층 도착
		ele.currentFloor = dest.arrive(destination, dest.asc, ele.count);

		// 승강기 재운행 여부
		cout << "\n모든 목적지 층에 도착했습니다. 승강기를 재운행 할까요? (재운행하려면 y입력) : ";
		cin >> run;
		cout << "\n================================================================================\n";

		//메모리 해제
		delete[] destination;
	}
	cout << "\n승강기 운행을 종료합니다." << endl;
}