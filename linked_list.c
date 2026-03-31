#include <stdio.h>
#include <stdlib.h>


/*일반적인 배열은 연속적인 메모리 공간을 차지하지만 연결리스트는 노드가 메모리에 비연속적으로 분포해있다*/
typedef struct Node { //노드 구조체 정의
	int data; //내가 저장할 데이터값
	struct Node* next; //다음 노드의 주소
} Node;


Node* create_node(int value) { //노드 생성
	Node* new_node = (Node*)malloc(sizeof(Node)); //포인터 변수 선언(동적메모리할당)
	new_node->data = value; //포인터 변수인 new_node한테 구조체 변수를 가져오라고 하는거임(데이터 저장)
	new_node->next = NULL; //아직 다음 노드 주소가 없음
	return new_node;	//새 노드 주소 반환
}



void push_front(Node** head, int value) { //맨 앞에 노드 삽입,,, 여기서 haed는 첫번째 노드를 가리키는 포인터임
	/*/왜 *가 두개나 붙었냐? > 하나만 썼을 때: head 포인터를 그냥 넘기면 함수 안에서 head를 바꿔도 원본은 그대로임
	그렇기 때문에 Node*에서 head의 주소를 넘기기 위해 두개를 쓰는거임, 즉, 포인터의 주소를 담는거 ㅇㅇ*/
	Node* new_node = create_node(value); /*앞에서 만든 create_node 함수를 호출해서 힙에 새 노드를 만들고,
											그 주소를 new_node에 저장*/
	new_node->next = *head; // *head는 지금 리스트의 첫 번째 노드 주소임, 즉 내가 지금 삽입하는 새로운 노드에 있는 next가 원래의 첫 노드를 가리키게 하는거
	*head = new_node; //이거는 head가 새로운 들어온 노드(이젠 맨 앞 노드)의 주소를 가리키게 하는거

}


void push_back(Node** head, int value) { //푸시백이라고 끝에 바로 삽입 안됨. 이놈도 배열이기 때문에 처음부터 들어가야함.
	Node* new_node = create_node(value);
	if (*head == NULL) { //만약에 리스트가 비어있다면 그냥 새로운 노드 넣고 끝( 밑에 줄은 head가 새 노드 주소를 가리키게 해주는거임 그리고 return으로 함수 끝냄)
		*head = new_node;
		return;
	}
	Node* rep = *head; /*여기서 포인터 변수를 왜 또 만드냐 ? 헤드를 직접 이동 시키면 문제가 생김 ㅇㅇ
	헤드는 항상 첫번째 노드를 가리켜야 하는데, 마지막 노드를 찾으러 이동하다 보면 헤드의 위치가 바뀌어버림
	그러면 리스트의 시작점 주소를 잃어버리게 되니까 ㅈ됨. 그래서 rep 이라는 복사본을 만들어서 그걸 이동시키는거임 ㅇㅇ*/
	while (rep->next != NULL) { //rep는 head니까 걍 헤드라고 하겟슴. 헤드의 주소가 비어있을 때까지 계속 돌려서 리스트의 마지막에 도달하게 하는거임
		rep = rep->next;
	}
	rep->next = new_node; /*바로 위에 줄에서 리스트의 마지막에 도달햇잖슴 ?
	그러면 그 마지막 노드가 가리키는 주소는 비어있겠지 그래서 그 빈 자리에 새로운 노드를 넣어주는거*/
}



// 각 노드의 데이터 값을 차례대로 모두 출력해버림
void print_list(Node* head) {
	Node* rep = head;
	while (rep != NULL) {
		printf("%d -> ", rep->data);
		rep = rep->next;
	}
	printf("NULL\n");
}



//특정 값을 삭제해보자
void delete_node(Node** head, int value) {
	if (*head == NULL) return;

	if ((*head)->data == value) { //내가 지우려는 값이 헤드가 가리키는 데이터값과 일치한다면
		Node* temp = *head; /*/첫번째를 가리키는 헤드를 임시로 만든 포인터 변수에 할당해줌.. 왜냐?
								나중에 free()를 해야하는데 *head를 그대로 갖다 써버리면 첫번째 노드의 주소를 잃어버림 ㅈㅈ*/
		*head = (*head)->next; //이제 헤드가 두번째 노드를 가리키게 바꿈. 그러면 첫번째에 있던 노드는 집을 잃어버림 ㅋㅋ야르
		free(temp); //이제 free를 이용해서 아까 저장해뒀던 주소로 첫 번째 노드 메모리를 해제함 진짜 뿅하고 사라짐
		return;
	}

	Node* rep = *head;
	while (rep->next != NULL && rep->next->data != value) {
		rep = rep->next;
	}
	if (rep->next != NULL) {
		Node* temp = rep->next; //삭제할 노드 주소가 지금 rep 다음에 있는 주소임 그래서 그 삭제할 주소를 temp에 저장하는거 temp에 넣어서 없애버릴라고
		rep->next = temp->next; //내가 temp를 없앨거니까 그 전후에 있는 노드들을 연결해주기 위해서 temp다음에 있는 노드를 rep 다음 노드로 넣어주는거
		free(temp);
	}
}


//전체 메모리 해제
void free_list(Node* head) {
	Node* rep = head;
	while (rep != NULL) {
		Node* temp = rep->next;  //다음 노드의 주소를 미리 저장한다 이유는 아까 위에서와 같이 주소를 잃어버리기 때문
		free(rep); //다음 노드의 주소를 저장했으면 그 전 노드는 해제
		rep = temp; //전 노드를 해제했으면 그 다음 노드가 들어있는 temp를 다시 rep해 할당 이거 반복
	}
}

int main() {
	Node* head = NULL;

	push_back(&head, 10);
	push_back(&head, 20);
	push_back(&head, 30);
	push_front(&head, 5);

	print_list(head);       // 5 -> 10 -> 20 -> 30 -> NULL

	delete_node(&head, 20);
	print_list(head);       // 5 -> 10 -> 30 -> NULL

	free_list(head);        // 모든 노드 메모리 해제
	return 0;
}

