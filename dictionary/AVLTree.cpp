#include "AVLTree.h"

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree()
{

    std::function<void(Node *)> deleteNode = [&](Node *node)
    {
        if (node)
        {
            deleteNode(node->left);
            deleteNode(node->right);
            delete node;
        }
    };
    deleteNode(root);
}

int AVLTree::getNodeHeight(AVLNode *node) const
{
    return node ? node->height : 0;
}

void AVLTree::updateHeight(AVLNode *node)
{
    if (node)
    {
        node->height = 1 + std::max(getNodeHeight(static_cast<AVLNode *>(node->left)),getNodeHeight(static_cast<AVLNode *>(node->right)));
    }
}

int AVLTree::getBalance(AVLNode *node) const
{
    if (!node)
        return 0;
    return getNodeHeight(static_cast<AVLNode *>(node->left)) -
           getNodeHeight(static_cast<AVLNode *>(node->right));
}

AVLTree::AVLNode *AVLTree::rightRotate(AVLNode *y)
{
    AVLNode *x = static_cast<AVLNode *>(y->left);
    AVLNode *T2 = static_cast<AVLNode *>(x->right);

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLTree::AVLNode *AVLTree::leftRotate(AVLNode *x)
{
    AVLNode *y = static_cast<AVLNode *>(x->right);
    AVLNode *T2 = static_cast<AVLNode *>(y->left);

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

void AVLTree::insert(const std::string &key, const std::string &value)
{
    std::function<AVLNode *(AVLNode *, const std::string &, const std::string &)> insertRec =
        [&](AVLNode *node, const std::string &k, const std::string &v) -> AVLNode *
    {
        if (!node)
            return new AVLNode(k, v);

        if (k < node->key)
            node->left = insertRec(static_cast<AVLNode *>(node->left), k, v);
        else if (k > node->key)
            node->right = insertRec(static_cast<AVLNode *>(node->right), k, v);
        else
        {
            node->value = v;
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && k < static_cast<AVLNode *>(node->left)->key)
            return rightRotate(node);

        if (balance < -1 && k > static_cast<AVLNode *>(node->right)->key)
            return leftRotate(node);

        if (balance > 1 && k > static_cast<AVLNode *>(node->left)->key)
        {
            node->left = leftRotate(static_cast<AVLNode *>(node->left));
            return rightRotate(node);
        }

        if (balance < -1 && k < static_cast<AVLNode *>(node->right)->key)
        {
            node->right = rightRotate(static_cast<AVLNode *>(node->right));
            return leftRotate(node);
        }

        return node;
    };

    root = insertRec(root, key, value);
}

std::string *AVLTree::find(const std::string &key)
{
    AVLNode *current = root;
    while (current)
    {
        if (key < current->key)
            current = static_cast<AVLNode *>(current->left);
        else if (key > current->key)
            current = static_cast<AVLNode *>(current->right);
        else
            return &(current->value);
    }
    return nullptr;
}

bool AVLTree::remove(const std::string &key)
{
    std::function<AVLNode *(AVLNode *, const std::string &)> removeRec =
        [&](AVLNode *node, const std::string &k) -> AVLNode *
    {
        if (!node)
            return nullptr;

        if (k < node->key)
            node->left = removeRec(static_cast<AVLNode *>(node->left), k);
        else if (k > node->key)
            node->right = removeRec(static_cast<AVLNode *>(node->right), k);
        else
        {
            if (!node->left || !node->right)
            {
                AVLNode *temp = static_cast<AVLNode *>(node->left ? node->left : node->right);
                if (!temp)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                delete temp;
            }
            else
            {
                AVLNode *temp = static_cast<AVLNode *>(node->right);
                while (temp->left)
                    temp = static_cast<AVLNode *>(temp->left);
                node->key = temp->key;
                node->value = temp->value;
                node->right = removeRec(static_cast<AVLNode *>(node->right), temp->key);
            }
        }

        if (!node)
            return nullptr;

        updateHeight(node);
        int balance = getBalance(node);

        if (balance > 1 && getBalance(static_cast<AVLNode *>(node->left)) >= 0)
            return rightRotate(node);

        if (balance > 1 && getBalance(static_cast<AVLNode *>(node->left)) < 0)
        {
            node->left = leftRotate(static_cast<AVLNode *>(node->left));
            return rightRotate(node);
        }

        if (balance < -1 && getBalance(static_cast<AVLNode *>(node->right)) <= 0)
            return leftRotate(node);

        if (balance < -1 && getBalance(static_cast<AVLNode *>(node->right)) > 0)
        {
            node->right = rightRotate(static_cast<AVLNode *>(node->right));
            return leftRotate(node);
        }

        return node;
    };

    bool existed = find(key) != nullptr;
    if (existed)
        root = removeRec(root, key);
    return existed;
}

int AVLTree::getHeight() const
{
    return getNodeHeight(root);
}

void inOrderTraversal(AVLTree::AVLNode* node) {
    if (node == nullptr) return;
    inOrderTraversal(static_cast<AVLTree::AVLNode*>(node->left));
    std::cout << "Ключ: " << node->key << ", Значение: " << node->value << std::endl;
    inOrderTraversal(static_cast<AVLTree::AVLNode*>(node->right));
}
void printTree(AVLTree &tree) {
    
    if (tree.root == nullptr) return;
    inOrderTraversal(tree.root);
    
}
