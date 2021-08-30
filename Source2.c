#include <stdio.h>
#include<stdbool.h>

#define SIZE 100

typedef struct TreeNode* TreeNodePtr;
struct TreeNode {
	char items[SIZE];
	TreeNodePtr left;
	TreeNodePtr right;
};
TreeNodePtr makeNode(char items[10]) {
	TreeNodePtr p = (TreeNodePtr)malloc(sizeof(struct TreeNode));
	strcpy(p->items, items);
	p->left = p->right = NULL;
	return p;
}
typedef struct Stack Stack;
struct Stack {
	TreeNodePtr data;
	Stack* next;
};
void push(Stack** top, TreeNodePtr data) {
	Stack* p = (Stack*)malloc(sizeof(Stack));
	p->data = data;
	p->next = NULL;
	if (!*top) {
		*top = p;
	}
	else {
		p->next = *top;
		*top = p;
	}
}
TreeNodePtr pop(Stack** top) {
	if (!*top) {
		return NULL;
	}
	TreeNodePtr x = (*top)->data;
	Stack* temp = *top;
	*top = (*top)->next;
	free(temp);
	return x;
}
TreeNodePtr peek(Stack** top) {
	if (!*top) {
		return NULL;
	}
	TreeNodePtr x = (*top)->data;
	return x;
}


int isOperand(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
int isOperator(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
int precedence(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '^':
		return 3;
	}
	return -1;
}
bool isEmpty(Stack** top)
{
	return (!*top);
}
/*int full(stackptr s) {

	return (s->top == SIZE - 1);

}
int size(stackptr s) {

	return strlen(s->item);
}
*/
/*
stackptr getStack() {

	stackptr stack = (stackptr)malloc(sizeof(struct stack));

	if (!stack)
		return NULL;

	stack->top = -1;
	return stack;
}
*/
/* stacknodeptr getStack() {

	stacknodeptr stack = (stacknodeptr)malloc(sizeof(struct nstack));

	if (!stack)
		return NULL;

	stack->top = -1;
	return stack;
} */
/*
char* copyString(char* destination, char* source)
{
	char* start = destination;

	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';
	return start;
}
*/
/*
void insert(TreeNodePtr* root,stackptr stack) {
	if (*root == NULL)
		*root = makeTreeNode(stack);
	else if (stack <= (*root))
		insert(&(*root)->left, stack);
	else
		insert(&(*root)->right, stack);
} */
void printPreOrder(TreeNodePtr root) {
	if (root != NULL) {
		for (int i = 0; i < strlen(root->items); i++)  //aamlha f kolo
			printf("%d ", root->items[i]);

		printPreOrder(root->left);
		printPreOrder(root->right);
	}
}
void printPostOrder(TreeNodePtr root) {
	if (root != NULL) {
		printPostOrder(root->left);
		printPostOrder(root->right);
		for (int i = 0; i < strlen(root->items); i++)
			printf("%c ", root->items[i]);
	}
}
void printInOrder(TreeNodePtr root, int prec) { // 3eeeetlttttttttttt
	if (root != NULL)
	{
		printInOrder(root->left, precedence(root->left));

		for (int i = 0; i < strlen(root->items); i++)
			if (precedence(root->items[i]) > precedence(root->left))
			{
				if (((root->left)->left != NULL) && ((root->left)->right != NULL))
				{
					printf("(");
					printf("%d ", root->items[i]);
					printf(")");
				}
				else
					printf("%d ", root->items[i]);
			}

		printInOrder(root->right, precedence(root->right));

		if (isOperator(root->items[0]))
		{

		}
		prec = precedence(root);
		if (precedence(root) > precedence(root->left))

			//law w2ef 3la root w parent le priority 23la ybaa mhtaga ahot parentheses
			//bs lw leaf msh hyb2a leha parentheses (a)
			printInOrder(root->left, prec);
		printf("%c ", root);
		printInOrder(root->right, prec);
	}
}


bool validatePost(char item[])
{
	int c = 0;
	int size = strlen(item);
	for (int i = 0; i < size; i++)
	{
		if (isOperand(item[i]))
			c++;
		if (isOperator(item[i])) {
			c -= 2; //done
			if (c < 0)
				return false;
			//printf("INVALID POSTFIX EXPRESSION");
			else
				c++; //as a left hand side
		}
	}
	if (c != 1)
		return false;
	//printf("INVALID POSTFIX EXPRESSION");

	else
		return true;
}
int validatePre(int start, char item[])
{
	int c = 0;
	int size = strlen(item);
	if (isOperator(item[0])) {
		c += 2;
		start++;
	}
	else
		return -1;

	int operandCount = 0; // check only next 2 operands //return position with answer from recursion
	for (int i = start; i < size; i++)
	{
		if (operandCount == 2)
			break;
		else if (isOperand(item[i])) {
			c--;
			operandCount++;
		}
		else if (isOperator(item[i])) {
			if (validatePre(i, item) == 0)
			{
				c--;
				i = i + 6; //skip operator with 2 operands
			}

		}
	}

	return c;
}

//bool validateIn() {//using stack }

	char* subStr(char str[])
	{
		char newStr[10] = { NULL };
		int count = 0;
		for (int i = 0; i < strlen(str); i++)
		{
			if (str[i] != ' ')
			{
				newStr[i] = str[i];
				count++;
			}
			else
				break;
		}
		newStr[count] = '\0';
		return newStr;
		//bt2ra lehd space
	}

	TreeNodePtr convertPost2Tree(Stack * stack, char item[]) {
		int temp = 0;
		while (strlen(item) > 0)
		{
			if (item[0] == ' ')
				item++;

			char tempStr[50] = { NULL };
			strcpy(tempStr, subStr(item));
			TreeNodePtr node = makeNode(tempStr);
			if (isOperand(item[0])) {
				push(&stack, node);
			}
			else if (isOperator(item[0])) {
				node->right = pop(&stack);
				node->left = pop(&stack);
				push(&stack, node);
			}

			//remove first part till the space
			int k = 0;
			while (k < strlen(item))
			{
				if (item[k] == ' ')
				{
					//remove the first part of the string including the space
					item = item + k + 1;
					break;
				}
				k++;
			}

		}

		return pop(&stack);

	}
	TreeNodePtr convertPre2Tree(Stack * stack, char item[]) {
		int temp = 0;
		while (strlen(item) > 0)
		{
			if (item[0] == ' ')
				item++;

			char tempStr[50] = { NULL };
			strcpy(tempStr, subStr(item));
			TreeNodePtr node = makeNode(tempStr);
			if (isOperator(item[0])) {
				push(&stack, node);
			}
			else if (isOperand(item[0])) {

				TreeNodePtr parentNode = pop(&stack);
				if (parentNode->left == NULL)
				{
					parentNode->left = node;
					push(&stack, parentNode);
				}
				else if (parentNode->right == NULL)
				{
					parentNode->right = node;
					push(&stack, parentNode);
				}
				else
				{

					TreeNodePtr grandParentNode = pop(&stack);
					grandParentNode->left = parentNode;
					grandParentNode->right = node;
					push(&stack, grandParentNode);
				}

			}

			//remove first part till the space
			int k = 0;
			while (k < strlen(item))
			{
				if (strlen(item) == 1) //last item
				{
					item = item + 1;
					break;
				}
				else if (item[k] == ' ')
				{
					//remove the first part of the string including the space
					item = item + k + 1;
					break;
				}
				k++;
			}

		}
		while (true)
		{
			TreeNodePtr node = pop(&stack);
			if (!isEmpty(stack))
			{
				TreeNodePtr temp = pop(&stack);
				if (temp->left == NULL)
				{
					temp->left = node;
					push(&stack, temp);
				}
				else if (temp->right == NULL)
				{
					temp->right = node;
					push(&stack, temp);
				}
			}
			else
			{
				return node;
			}
		}

	}

	void convertIn2Tree(Stack * stack, char item[]) {}




	int main() {

		//Stack stack=ngetStack();
		Stack* top = NULL;
		while (1)
		{
			int choice = 0;
			printf("Please choose an option:-\n 1- Input prefix\n 2-Input infix\n 3- Input postfix\n 0-Exit\n >>input:");
			scanf_s("%d", &choice);

			switch (choice)
			{
			case 1: {  char input[50] = { NULL };
				  int length = 0;
				  printf("Prefix input: ");
				  gets(input);
				  gets(input);

				  if (validatePre(0, input) != 0)
				  {
					  printf("Prefix input is not correct!");
					  break;
				  }
				  TreeNodePtr Tree = convertPre2Tree(&top, input); //de han7ot el return bta3ha fe treenode 3shan nst5dmoooo
				  printf("prefix: ");
				  length = strlen(input);
				  for (int i = 0; i <= length; i++)
					  printf("%c", input[i]);
				  printf("\n");

				  /*printf("infix:\t");
				  printInOrder(stack,input);
				  */
				  printf("postfix: ");
				  printPostOrder(Tree);

			}

				  /*
			  case 2: {
					char input[50] = { NULL };
					int length = 0;
					printf("Infix input: ");
					gets(input);
					gets(input);
					length = strlen(input);
					convertIn2Tree(stack, input);
					validateIn(); //mhtagaaaa atcheck kol l infix
					printf("prefix:\t");
					printPreOrder(stack, input);
					printf("infix:\t");
					for (int i = 0; i <= strlen(input); i++)
						printf("%c\n", input[i]);
					printf("postfix:\t");
					printPostOrder(stack, input);

			  }
			  */
			case 3: {
				char input[50] = { NULL };
				int length = 0;
				printf("Postfix input: ");
				gets(input);
				gets(input);
				length = strlen(input);
				convertPost2Tree(top, input);
				validatePost(top, input);
				printf("prefix:\t");
				printPreOrder(top, input);
				/* printf("infix:\t");
				 printInOrder(stack, input);
				 */ printf("postfix:\t");
				 for (int i = 0; i <= strlen(input); i++)
					 printf("%c\n", input[i]);
			}
			case 0: break;
			default: printf("Please choose a valid option!\n ");
				continue;
			}

			return 0;
		}




		/*
		TreeNodePtr root = NULL;
		insert(&root, 6);
		insert(&root, 3);
		insert(&root, 10);
		insert(&root, 1);
		insert(&root, 19);
		insert(&root, 2);
		insert(&root, 7);
		insert(&root, 5);
		printf("Pre-Order:\t");
		preOrder(root);

		printf("\nPost-Order:\t");
		postOrder(root);

		printf("\nIn-Order:\t");
		inOrder(root);

		return 0;
		*/
	}



	/*
	void readPre(stackptr stack, char item[]) { //a3mlehaa


		stackptr stack2;
		int temp = 0;
		while (strlen(item) > 0)
		{
			if (item[0] == ' ')
				item++;

			TreeNodePtr node = makeTreeNode(subStr(item));
			if (isOperand(item[0])) {
				push(stack, node);
			}
			if (isOperator(item[0])) {

					while (peek(stack2) != '$' && precedence(item[0]) <= precedence(peek(stack2)))
					{
						char c = peek(stack2);
						pop(stack2);
					 TreeNodePtr node = makeTreeNode(c);
					 node->right = pop(stack);
					 node->left = pop(stack);
					 push(stack, node);


					}
				push(stack2, item[0]);
				int k = 0;
				while (k < strlen(item))
				{
					if (item[k] == ' ')
					{
						item = item + k + 1;
						break;
					}
					k++;
				}

			}


		}

		pop(stack);



	}
	*/

	/*
	struct stack {
		int top;
		char item[SIZE];
	};
	typedef struct stack* stackptr;

	typedef struct TreeNode* TreeNodePtr;
	struct TreeNode {
		char items[SIZE];
		TreeNodePtr left, right;
	};

	struct nstack {
		int top;
		TreeNodePtr item[SIZE];
	};
	typedef struct nstack* stacknodeptr;

	void removeSpaces(char* str)
	{

		int count = 0;

		for (int i = 0; str[i]; i++)
			if (str[i] != ' ')
				str[count++] = str[i];

		str[count] = '\0';
	}
	bool isEmpty(stackptr s)
	{
		return (s->top == -1);
	}
	bool nisEmpty(stacknodeptr s)
	{
		return (s->top == -1);
	}
	char peek(stackptr s)
	{
		return s->item[s->top];
	}
	char npeek(stacknodeptr s)
	{
		return s->item[s->top];
	}
	char pop(stackptr s)
	{
		if (!isEmpty(s))
		{
			return s->item[s->top--];
		}
		return '$';
	}
	char npop(stacknodeptr s)
	{
		if (!isEmpty(s))
		{
			return s->item[s->top--];
		}
		return '$';
	}
	void push(stackptr s, char inp)
	{
		s->item[++s->top] = inp;
	}
	void npush(stacknodeptr s, char inp)
	{
		s->item[++s->top] = inp;
	}
	*/