#include <iostream>
#include <fstream>

class listNode{
	public:
	int data;
	listNode* next;
	//methods
	listNode(int newData){
		this->data = newData;
		this->next = nullptr;
	}
	void printNode(std::ofstream& output){
		if(this->next == nullptr){
			output<<"(nodes data: "<<this->data<<", nexts data: NULL)\n";
		}
		else{
			output<<"(nodes data: "<<this->data<<", nexts data: "<<this->next->data<<")\n";
		}
	}
};

class LLStack{
	public:
	listNode* top;
	//methods
	LLStack(){
		this->top = new listNode(-99999);
	}
	void push(listNode* node){
		if(this->top->next == nullptr){
			//empty list add new node
			this->top->next = node;
		}
		else{
			node->next = this->top->next;
			this->top->next = node;
		}
	}
	bool isEmpty(){
		if(this->top->next == nullptr){
			return true;
		}
		return false;
	}
	listNode* pop(std::ofstream& output){
		if(this->isEmpty()){
			output<<"Stack is empty"<<std::endl;
			return nullptr;
		}
		else{
			listNode* temp = this->top->next;
			this->top->next = this->top->next->next;
			output<<temp->data<<std::endl;
			return temp;
		}
	}
	void buildStack(std::ifstream& input){
		int number;
		while(input >> number){
			listNode* newNode = new listNode(number);
			this->push(newNode);
		}
	}
	//debug
	/*
	void printStack(std::ofstream& output){
		listNode* reader = this->top;
		while(reader->next != nullptr){
			reader->next->printNode(output);
			reader = reader->next;
		}
	}
	*/
};

class LLQueue{
	public:
	listNode* head;
	listNode* tail;
	
	//methods
	LLQueue(){
		listNode* dummy = new listNode(-99999);
		
		this->head = new listNode(-1);
		this->tail = new listNode(-1);
		
		this->head->next = dummy;
		this->tail->next = dummy;
	}
	bool isEmpty(){
		if(this->tail->next == this->head->next){
			return true;
		}
		return false;
	}
	void insertQ(listNode* node){
		node->next = nullptr;
		if(this->isEmpty()){
			this->head->next->next = node;
			this->tail->next = node;
		}
		else{
			this->tail->next->next = node;
			this->tail->next = node;
		}
	}
	listNode* deleteQ(std::ofstream& output){
		if(this->isEmpty()){
			output<<"Queue is empty\n";
			return nullptr;
		}
		if(this->head->next->next == this->tail->next){
			listNode* temp = this->head->next->next;
			this->tail->next = this->head->next;
			this->head->next->next = nullptr;
			return temp;
		}
		else{
			listNode* temp = this->head->next->next;
			this->head->next->next = this->head->next->next->next;
			return temp;
		}
		listNode* temp = this->head->next->next;
		//head -> dummy -> node      head -> dummy -> node -> next node
		this->head->next->next = this->head->next->next->next;
		output<<temp->data<<std::endl;
		return temp;
	}
	void buildQueue(std::ofstream& output, LLStack stack){
		while(!stack.isEmpty()){
			listNode* temp = stack.pop(output);
			this->insertQ(temp);
		}
	}
	//debug
	/*
	void printQueue(std::ofstream& output){
		listNode* reader = this->head;
		while(reader->next != nullptr){
			reader->next->printNode(output);
			reader = reader->next;
		}
	}
	*/
};

class LList{
	public:
	listNode* listHead;
	//methods
	LList(){
		this->listHead = new listNode(-1);
		this->listHead->next = new listNode(-99999);
	}
	listNode* findSpot(listNode* node){
		listNode* spot = this->listHead;
		while(spot->next != nullptr && spot->next->data < node->data){
			spot = spot->next;
		}
		return spot;
	}
	void insertOneNode(listNode* node){
		listNode* spot = this->findSpot(node);
		node->next = spot->next;
		spot->next = node;
	}
	void buildList(std::ofstream& output, LLQueue queue){
		while(!queue.isEmpty()){
			listNode* temp = queue.deleteQ(output);
			output<<temp->data<<std::endl;
			this->insertOneNode(temp);
		}
	}
	void printList(std::ofstream& output){
		listNode* reader = this->listHead;
		while(reader->next != nullptr){
			reader->next->printNode(output);
			reader = reader->next;
		}
	}
};

int main(int argc, char* argv[]){
	//check arguments
	if(argc != 5){
		std::cout<<"You must include 4 arguments (inFile, outFile1, outFile2, outFile3)"<<std::endl;
		return -1;
	}
	//read input file
	std::ifstream input(argv[1]);
	if(!input.good()){
		std::cout<<"Invalid input file, please check the spelling!"<<std::endl;
		return -1;
	}
	input.close();
	//outfile creation
	std::ofstream output1;
	std::ofstream output2;
	std::ofstream output3;
	//step 1 create LL stack
	LLStack stack;
	//step 2 build stack
	input.open(argv[1]);
	stack.buildStack(input);
	input.close();
	//step 3 create queue
	LLQueue queue;
	//step 4 build queue
	output1.open(argv[2],std::ios::out | std::ios::app);
	queue.buildQueue(output1, stack);
	output1.close();
	//step 5 create list
	LList list;
	//step 6 build list
	output2.open(argv[3],std::ios::out | std::ios::app);
	list.buildList(output2, queue);
	output2.close();
	//step 7 print list
	output3.open(argv[4],std::ios::out | std::ios::app);
	list.printList(output3);
	output3.close();
}