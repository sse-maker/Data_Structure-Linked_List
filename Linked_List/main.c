//
//  main.c
//  Linked_List
//
//  Created by 세광 on 2021/07/29.
//

/*
 <링크드 리스트(Linked List)란?>
 배열의 단점을 보완하기 위한 자료 구조
 각각의 원소가 포인터를 사용하여 다음 원소의 위치를 가리킴 (포인터를 사용하여 자료들을 연결하는 방법)
 중간에 자료를 삽입하거나 삭제할 경우, 배열처럼 뒤의 자료를 모두 이동할 필요 없이 해당 줄의 연결 위치만 변경하면 됨
 자료를 저장할 공간이 필요할 때마다 동적으로 메모리 공간을 생성하여 쉽게 추가할 수 있음
 
 <링크드 리스트 구조>
 링크드 리스트는 노드의 집합
 노드는 데이터 필드(data field)와 링크 필드(link field)로 구성되어 있음
 노드의 데이터 필드에는 저장할 자료가 저장되고, 링크 필드에는 다른 노드를 가리키는 포인터가 저장됨
 데이터 필드에 저장할 자료로는 정수뿐만 아니라 서로 다른 자료형으로 구성된 구조체와 같은 복잡한 자료들도 가능
 링크드 리스트에서는 링크 필드에 사용하는 포인터를 이용하여 다음 노드를 연결할 수 있으며, 반드시 첫 번째 노드를 알고 있어야 전체 노드에 접근할 수 있는 구조이다. 그래서 첫 번째 노드를 가리키고 있는 변수가 필요한데, 이 포인터를 헤드 포인터(Head Pointer)라 한다. 링크드 리스트의 이름이 이 헤드 포인터의 이름과 같다고 생각하면 된다. 링크드 리스트에 노드가 하나도 없다면 헤드 포인터는 널 값을 가지며, 이 링크드 리스트를 공백 링크드 리스트라 한다. 링크드 리스트에서 마지막 노드의 링크 필드는 NULL로 설정되는데, 이는 더 이상 연결된 노드가 없다는 의미이다.
 링크드 리스트에서의 노드들은 배열과 다르게 하드웨어 메모리 공간 내의 어느 주소에나 위치할 수 있음 (노드들은 리스트상의 순서와 동일하지 않아도 됨)
 링크드 리스트를 사용하면 연속적인 메모리 공간이 없더라도 자료를 저장하고 순서를 저장할 수 있으며, 미리 저장할 메모리 공간을 확보해 놓을 필요가 없음; 필요할 때마다 노드를 동적으로 생성하여 연결하면 되기 때문
 
 <자기 참조 구조체>
 자기 참조 구조체(Self-Referential Structure)는 특별한 구조체로서 구조체 자신과 동일한 자료형의 구조체를 가리키는 포인터를 멤버로 포함하는 구조체
 기본적인 자기 참조 구조체 형태 - 아래의 문장은 node라는 구조체를 정의한 것인데, 이 구조체 내에는 자기 자신인 node 구조체를 가리키는 포인터를 멤버로 가지고 있음
 struct node {
    int data;
    struct node *link;
 };
 일반적으로 자기 참조 구조체는 typedef 키워드를 사용하여 새로운 자료형 이름으로 재정의하여 사용 (typedef를 사용하면 매번 struct 키워드를 적지 않아도 되므로 코드를 간소화할 수 있음)
 typedef struct node {
    int data;
    struct node *link;
 } NODE; // 구조체 node를 NODE로 재정의
 */

#include <stdio.h>
#include <stdlib.h>

// <0. 링크드 리스트를 구현하기 위한 노드의 구조 정의>
typedef struct node {
    int number;
    struct node *link;
} NODE;

/*
 <2. 링크드 리스트 삽입>
 링크드 리스트에서 자료를 삽입하기 위한 방법 - 첫 번째 노드로 삽입하는 경우, 중간 노드로 삽입하는 경우, 마지막 노드로 삽입하는 경우
 첫 번째 노드로 삽입하는 경우 새 노드의 링크 필드가 기존의 첫 번째 노드를 가리키도록 한 다음, 헤드 포인터가 삽입되는 새 노드를 가리키도록 함 (링크 필드를 변경하는 순서에 주의)
 만약 링크드 리스트에 노드가 하나도 없는 상황이라면 헤드 포인터 ptr_head에 저장되어 있는 NULL이 새로 생성되는 포인터 ptr_new의 링크 필드에 저장되고, ptr_new의 주소값이 헤드 포인터 ptr_head의 값이 되어 ptr_head가 ptr_new를 가리키게 됨 (문제가 발생하지 않음)
 중간 노드로 삽입할 경우에는 반드시 이전 노드를 가리키는 포인터가 필요함
 새 노드를 생성한 다음, 새 노드의 링크 필드는 이전 노드의 링크 필드가 가리키는 노드를 가리키게 하고, 이전 노드의 링크 필드가 새 노드를 가리키도록 함 (링크 필드를 변경하는 순서에 주의)
 이전 노드를 가리키는 ptr_prev 포인터는 추후 NODE *search_last(NODE *ptr_head) 함수를 호출하여 검색
 
 노드 삽입을 위한 insert_node() 함수는 인수로 헤드 포인터, 이전 노드 포인터, 새 노드 포인터를 전달받음
 만약 인수 ptr_prev가 NULL이면 링크드 리스트의 첫 번째 노드로 삽입하고, 그렇지 않으면 중간 노드로 삽입
 혹시라도 변경되었을 수도 있는 헤드 포인터 값을 반환하고, 호출 함수에서는 이 반환값을 원본 헤드 포인터에 대입
 */
NODE *insert_node(NODE *ptr_head, NODE *ptr_prev, NODE *ptr_new) {
    if (ptr_prev == NULL) { // 첫 번째 노드로 삽입
        ptr_new->link = ptr_head;
        ptr_head = ptr_new;
    } else { // 중간 노드로 삽입
        ptr_new->link = ptr_prev->link;
        ptr_prev->link = ptr_new;
    }
    return ptr_head;
}

/*
 마지막 노드로 삽입할 경우 먼저 헤드 포인터의 값이 NULL인지 검사하여 NULL이라면 헤드 포인터 다음에 연결, NULL이 아니라면 헤드 포인터부터 전체 노드를 순차적으로 검색하면서 해당 노드의 링크 필드 값이 NULL인 마지막 노드를 찾아서 이 노드의 링크 필드가 새로 만든 노드의 주소값을 가리키도록 함
 혹시라도 변경되었을 수도 있는 헤드 포인터 값을 반환하고, 호출 함수에서는 이 반환값을 원본 헤드 포인터에 대입
 */
NODE *append_node(NODE *ptr_head, NODE *ptr_new) {
    NODE *ptr_last = ptr_head;
    if (ptr_head == NULL) { // 헤드 포인터가 NULL이면 헤드 포인터에 연결
        ptr_head = ptr_new;
    } else { // 링크 필드가 NULL인 마지막 노드 ptr_prev 찾기
        while (ptr_last->link != NULL) {
            ptr_last = ptr_last->link;
        }
        ptr_last->link = ptr_new; // 마지막 노드의 링크를 새 노드에 연결
    }
    return ptr_head;
}

/*
 <3. 링크드 리스트 삭제>
 노드를 삭제할 경우 먼저 링크 필드들을 변경한 다음, 동적으로 할당된 메모리 공간을 반납하는 순서로 진행
 삽입과 마찬가지로 첫 번째 노드 삭제와 중간 노드 삭제를 구분해야 함 (이전 노드의 포인터(ptr_prev) 필요)
 링크드 리스트의 첫 번째 노드를 삭제하려면 이전 노드를 가리키는 포인터 ptr_prev는 NULL이 됨, 즉 삭제 함수에서는 ptr_prev가 NULL이면 첫 번째 노드를 삭제하고, ptr_prev가 NULL이 아니면 ptr_prev가 가리키는 다음 노드를 삭제
 첫 번째 노드를 삭제하는 경우 헤드 포인터를 첫 번째 노드의 다음 노드로 변경하고, 삭제할 노드가 차지하고 있던 동적 메모리 공간을 반납
 중간 노드를 삭제할 경우 ptr_prev가 NULL이 아니므로 ptr_prev가 가리키는 노드의 링크 필드가 삭제되는 노드 ptr_curr의 다음 노드를 가리키도록 함
 
 노드 삭제를 위한 delete_node() 함수는 인수로 헤드 포인터, 이전 노드 포인터, 현재 노드 포인터를 전달받음
 인수 ptr_prev가 NULL이면 첫 번째 노드를 삭제하고, 그렇지 않으면 중간 노드 삭제
 혹시라도 변경되었을 수도 있는 헤드 포인터 값을 반환하고, 호출 함수에서는 이 반환값을 원본 헤드 포인터에 대입
 */
NODE *delete_node(NODE *ptr_head, NODE *ptr_prev, NODE *ptr_curr) {
    if (ptr_prev == NULL) { // 첫 번째 노드 삭제
        ptr_head = ptr_curr->link;
    } else { // 중간 노드 삭제
        ptr_prev->link = ptr_curr->link;
    }
    free(ptr_curr);
    return ptr_head;
}

/*
 <4. 링크드 리스트 전체 삭제>
 링크드 리스트의 전체 노드를 삭제하기 위해 첫 번째 노드부터 순차적으로 삭제
 노드 이동에 사용할 새로운 포인터 ptr_curr에 헤드 포인터(ptr_head)를 저장해놓고, 다음 노드를 가리킬 포인터 ptr_next를 선언하여 생성해놓은 다음, 현재 포인터(ptr_curr)가 NULL이 아닌 동안 다음 순서를 반복적으로 수행하고, 반복을 종료하면 노드가 존재하지 않기 때문에 ptr_head에 NULL 저장
 현재 포인터(ptr_curr)의 링크 필드(link)를 다음 노드를 가리킬 포인터(ptr_next)에 저장 -> free() 함수의 인수로 헤드 포인터가 가리키는 현재 포인터(ptr_curr)를 전달하여 현재 포인터가 가리키는 노드의 메모리 공간 반납 -> 다음 노드를 가리키는 포인터(ptr_next)를 현재 노드를 가리키는 포인터(ptr_curr)에 저장
 */
NODE *delete_all(NODE *ptr_head) {
    NODE *ptr_curr = ptr_head;
    NODE *ptr_next = NULL;
    while (ptr_curr != NULL) {
        ptr_next = ptr_curr->link; // 현재 포인터의 링크를 다음 포인터에 저장
        free(ptr_curr); // 현재 포인터 반납
        ptr_curr = ptr_next; // 다음 포인터를 현재 포인터에 저장
    }
    ptr_head = NULL;
    return ptr_head;
}

/*
 <5. 링크드 리스트 순차 접근과 출력>
 링크드 리스트를 순차적으로 접근하기 위해서는 노드를 가리키는 포인터가 하나 필요, 이 포인터는 먼저 첫 번째 노드를 가리킴
 첫 번째 노드를 방문하고 난 후에 이 포인터를 첫 번째 노드의 링크를 따라 이동시켜 두 번째 노드를 가리키게 함
 두 번째 노드를 방문하고 난 후에 이 포인터를 두 번째 노드의 링크를 따라 이동시켜 세 번째 노드를 가리키게 함
 이러한 방식으로 링크드 리스트의 마지막 노드까지 접근하고 이 노드의 포인터 값이 NULL이면 종료하도록 구현
 
 순차 접근을 사용하면 링크드 리스트가 가지고 있는 모든 자료의 값을 화면에 출력할 수 있음
 */
void print_all(NODE *ptr_head) {
    NODE *ptr_curr = ptr_head; // ptr_curr의 초기값은 헤드 포인터
    while (ptr_curr != NULL) {
        printf("%d\n", ptr_curr->number);
        ptr_curr = ptr_curr->link; // ptr_curr이 다음 노드를 가리키도록 함
    }
}

/*
 순차 접근을 사용하여 노드의 전체 개수를 구하는 함수
 */
int get_total(NODE *ptr_head) {
    NODE *ptr_curr = ptr_head; // ptr_curr의 초기값은 헤드 포인터
    int total = 0;
    while (ptr_curr != NULL) {
        total++; // 반복 횟수 1 증가 (노드 개수 1 증가)
        ptr_curr = ptr_curr->link; // ptr_curr이 다음 노드를 가리키도록 함
    }
    return total;
}

/*
 예를 들어, 각 노드들이 정수값을 저장하고 있다고 가정했을 때 순차 접근을 사용하면 링크드 리스트 내에 저장되어 있는 이 정수들의 합계를 구할 수 있음
 */
int get_sum(NODE *ptr_head) {
    NODE *ptr_curr = ptr_head; // ptr_curr은 첫 번째 노드
    int sum = 0;
    while (ptr_curr != NULL) {
        sum += ptr_curr->number; // number는 정수값
        ptr_curr = ptr_curr->link; // ptr_curr이 다음 노드를 가리키도록 함
    }
    return sum;
}

/*
 <6. 링크드 리스트 검색>
 링크드 리스트에서의 자료 검색은 헤드 포인터부터 순차적으로 접근하여 검색
 */
NODE *search_node(NODE *ptr_head, int pos) {
    NODE *ptr_curr = ptr_head;
    if (pos > 0 && pos <= get_total(ptr_head)) {
        for (int i = 1; i < pos; i++) {
            ptr_curr = ptr_curr->link;
        }
    }
    return ptr_curr;
}

/*
 마지막 노드를 찾는 NODE *search_last(NODE *ptr_head) 함수
 */
NODE *search_last(NODE *ptr_head) {
    NODE *ptr_last = ptr_head;
    if (ptr_head == NULL) {
        ptr_last = ptr_head;
    } else {
        while (ptr_last->link != NULL) {
            ptr_last = ptr_last->link;
        }
    }
    return ptr_last;
}

/*
 이전 노드를 검색하는 NODE *search_prev(NODE *ptr_head, int pos) 함수
 
 pos가 1 이하의 값이면 노드가 존재하지 않기 때문에 ptr_prev에 NULL 저장
 pos가 1부터 전체 개수 이내의 수라면 이전 노드를 찾기 위해서 pos - 1의 노드를 찾음
 전체 개수보다 클 경우는 마지막 노드를 저장하기 위해 앞서 작성한 search_last() 함수 호출
 */
NODE *search_prev(NODE *ptr_head, int pos) {
    NODE *ptr_prev = ptr_head;
    if (pos <= 1) {
        ptr_prev = NULL;
    } else if (pos > 1 && pos <= get_total(ptr_head)) {
        for (int i = 1; i < pos - 1; i++) {
            ptr_prev = ptr_prev->link;
        }
    } else {
        ptr_prev = search_last(ptr_head);
    }
    return ptr_prev;
}

/*
 링크드 리스트를 역순으로 정렬하는 NODE *reverse_node(NODE *ptr_head) 함수
 
 이전 노드를 가리킬 ptr_prev와 다음 노드를 가리킬 ptr_next 포인터를 NULL로 초기화, 현재 노드를 가리킬 ptr_curr을 ptr_head로 초기화
 헤드 포인터가 NULL이면 노드가 비어 있다고 출력하고 함수 종료
 헤드 포인터 값을 가지고 있는 ptr_curr이 NULL이 아닌 동한 ptr_curr의 다음 노드를 ptr_next에 저장하고, ptr_prev를 ptr_curr에 저장
 ptr_curr을 ptr_prev에 저장하고 ptr_next를 ptr_curr에 저장하는 형태를 반복적으로 수행
 마지막으로 ptr_prev를 ptr_head로 저장하고 이 헤드 포인터를 반환
 */
NODE *reverse_node(NODE *ptr_head) {
    NODE *ptr_prev, *ptr_curr, *ptr_next;
    ptr_prev = NULL;
    ptr_next = NULL;
    ptr_curr = ptr_head;
    if (ptr_head == NULL) {
        puts("** 노드가 비어 있습니다 **");
        getchar();
        exit(1);
    }
    while (ptr_curr != NULL) {
        ptr_next = ptr_curr->link;
        ptr_curr->link = ptr_prev;
        ptr_prev = ptr_curr;
        ptr_curr = ptr_next;
    }
    ptr_head = ptr_prev;
    return ptr_head;
}

int main() {
    /*
     <1. 링크드 리스트 생성>
     새 노드를 생성하지 않은 상태
     */
    NODE *ptr_head = NULL; // 첫 번째 노드를 가리킬 헤드 포인터(ptr_head)
    NODE *ptr_new = NULL; // 새로 생성할 노드를 가리킬 포인터(ptr_new)
    
    /*
     링크드 리스트에서는 노드가 필요할 때마다 필요한 메모리 공간을 동적으로 할당받기 때문에 malloc() 함수를 호출하여 생성할 노드 크기만큼의 동적 메모리 공간을 운영체제로부터 할당받으면, 그 반환값을 NODE *형으로 형변환하여 ptr_new에 저장, 이렇게 할당받은 새로운 동적 메모리 공간이 첫 번째 노드가 됨
     새 노드가 생성되었으면 새 노드의 데이터 필드에 값을 저장하고 링크 필드에 NULL을 저장하여 마지막 노드임을 명시 (즉, 현재 동적으로 생성한 노드가 처음이자 마지막 노드가 됨)
     */
    ptr_new = (NODE *)malloc(sizeof(NODE));
    ptr_new->number = 10;
    ptr_new->link = NULL;
    ptr_head = ptr_new; // ptr_new의 값을 ptr_head에 저장함으로써 헤드 포인터가 새 노드를 가리키도록 함
    
    /*
     링크드 리스트는 여러 개의 노드가 서로 연결되어 있기 때문에 앞선 동일한 방법으로 두 번째 노드를 동적으로 생성하고, 이 노드가 마지막 노드이므로 데이터 필드에 값을 저장하고 링크 필드를 NULL로 저장한 다음, 첫 번째 노드의 링크 필드가 두 번째 노드를 가리키도록 하면 두 개의 노드가 연결됨
     링크드 리스트의 마지막 노드를 추가하기 위해 이러한 작업을 반복
     */
    ptr_new = (NODE *)malloc(sizeof(NODE));
    ptr_new->number = 20;
    ptr_new->link = NULL;
    ptr_head->link = ptr_new;
    
    /*
     동적으로 생성한 메모리 공간 사용을 마쳤으면 반드시 반납해주어야 함
     malloc() 함수를 호출하여 동적으로 메모리를 생성한 경우, 할당받은 메모리를 반납하기 위해 free() 함수 호출 (이때 인수로는 malloc() 함수 호출의 반환값으로 반환된 포인터를 전달, 프로그램이 종료되면 할당된 메모리 공간 회수)
     */
    free(ptr_head);
    free(ptr_new);
}
