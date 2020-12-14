//Karoliny Oliveira - 10368020
#include "treap.h"
#include "queue.h"
struct node
{
	int data, priority;
	node_t *left, *right;
};

//Assinatura de Funções Internas

/*
* Cria um novo nó da treap
*
* @param x chave
* @param prioridade
*
* @return ponteiro para o nó criado
*/
node_t *createNode(int x, int prioridade);

/*
* Rotaciona a subárvore no sentido antihorário
*
* @param root raíz da subárvore
*
* @return subárvore rotacionada
*/
node_t *rotateLeft(node_t *root);

/*
* Rotaciona a subárvore no sentido horário
*
* @param root raíz da subárvore
*
* @return subárvore rotacionada
*/
node_t *rotateRight(node_t *root);

//Percursos
void preOrder(node_t *root);
void inOrder(node_t *root);
void postOrder(node_t *root);
void bfs(node_t *root);

//Implementações

node_t *createNode(int x, int prioridade)
{
	node_t *newNode = (node_t *)malloc(sizeof(node_t));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = x;
	newNode->priority = prioridade;
	return newNode;
}

node_t *rotateLeft(node_t *root)
{
	node_t *child = root->right;
	node_t *childLeft = child->left;

	child->left = root;
	root->right = childLeft;

	return child;
}

node_t *rotateRight(node_t *root)
{
	node_t *child = root->left;
	node_t *childRight = child->right;

	child->right = root;
	root->left = childRight;

	return child;
}

treap_t *treap_create()
{
	treap_t *tree = (treap_t *)malloc(sizeof(treap_t));
	tree->root = NULL;
	return tree;
}

node_t *treap_insert(node_t *root, int x, int prioridade)
{
	if (!root)
		return createNode(x, prioridade);

	if (x == root->data)
	{
		printf("Elemento ja existente\n");
		return root;
	}

	if (x < root->data)
	{
		root->left = treap_insert(root->left, x, prioridade);

        // Ajuste da ordem Heap
		if (root->left->priority > root->priority)
			root = rotateRight(root);
	}
	else
	{
		root->right = treap_insert(root->right, x, prioridade);

        // Ajuste da ordem Heap
		if (root->right->priority > root->priority)
			root = rotateLeft(root);
	}
	return root;
}

node_t *treap_search(node_t *root, int x)
{
	if (!root)
		return NULL;
	if (root->data == x)
		return root;
	if (x < root->data)
		return treap_search(root->left, x);
	else
		return treap_search(root->right, x);
}

int treap_isEmpty(treap_t *t)
{
	if (!t)
		return 0;
	if (!t->root)
		return 1;
	return 0;
}

void treap_finish(node_t *root)
{
	if (root)
	{
		treap_finish(root->left);
		treap_finish(root->right);
		free(root);
	}
}

void treap_print(node_t *root, char *mode)
{
	if (!root)
		return;
	switch (mode[2])
	{
	    case 'd': //emOrdem
	    inOrder(root);
	    break;
	    case 's': //posOrdem
	    postOrder(root);
	    break;
	    case 'e': //preOrdem
	    preOrder(root);
	    break;
	    case 'r': //Largura
	    bfs(root);
	    break;
	    default:
	    break;
	}
	printf("\n");
	return;
}

node_t *treap_remove(node_t *root, int x, int prioridade)
{
	if (!root)
	{
		printf("Chave nao localizada\n");
		return root;
	}
	if (x < root->data)
		root->left = treap_remove(root->left, x, prioridade);
	else if (x > root->data)
		root->right = treap_remove(root->right, x, prioridade);

    // Filho esquerdo nulo
	else if (!root->left)
	{
		node_t *aux = root->right;
		free(root);
		root = aux;
	}

    // Filho direito nulo
	else if (!root->right)
	{
		node_t *aux = root->left;
		free(root);
		root = aux;
	}

    // Ambos os filhos são não nulos
	else 
	{
		root = rotateLeft(root);
		root->left = treap_remove(root->left, x, prioridade);
	}

	return root;
}

void preOrder(node_t *root)
{
	if (root)
	{
		printf("(%d, %d) ", root->data, root->priority);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(node_t *root)
{
	if (root)
	{
		inOrder(root->left);
		printf("(%d, %d) ", root->data, root->priority);
		inOrder(root->right);
	}
}

void postOrder(node_t *root)
{
	if (root)
	{
		postOrder(root->left);
		postOrder(root->right);
		printf("(%d, %d) ", root->data, root->priority);
	}
}

void bfs(node_t *root)
{
	if (!root)
		return;
	queue_t *Q = queue_create(sizeof(node_t *), 20);
	queue_insert(Q, (void *)&root);
	while (!queue_isEmpty(Q))
	{
		node_t *current;
		queue_remove(Q, (void *)&current);
		printf("(%d, %d) ", current->data, current->priority);

		if (current->left)
			queue_insert(Q, (void *)&current->left);
		if (current->right)
			queue_insert(Q, (void *)&current->right);
	}
	queue_destroy(Q);
	return;
}