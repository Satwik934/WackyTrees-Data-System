#include "wackman.h"

/**
 * Given an array of integers and its length, this function calculates
 * the sum of all the elements in the array.
 *
 * @pre The array size (array_size) must be greater than or equal to 0.
 *
 * @param int_array Pointer to the array of integers.
 * @param array_size The number of elements in the array.
 * @return The sum of all integers in the array.
 */
int sum_array_elements(int int_array[], int array_size) {
	int total = 0;
    for ( int i = 0; i < array_size; i++){
		total = total + int_array[i];
	}
	return total;
}

/**
 * Given an integer array of size ASCII_CHARACTER_SET_SIZE, this function
 * computes the number of occurrences of each ASCII character in the given
 * string. The results are stored in the corresponding indices of the
 * occurrence_array. The computation stops at and does not include the DELIMITER
 * character.
 *
 * @note The occurrence_array[0] should always be 0, representing the DELIMITER.
 * @note The ASCII decimal value of each character corresponds to its index in
 * the array. For example, 'F' with ASCII decimal value 70 will increment
 * occurrence_array[70].
 *
 * @param occurrence_array An array to store the occurrences of each ASCII
 * characters. The array size should be ASCII_CHARACTER_SET_SIZE.
 * @param string The input string to analyze for ASCII character occurrences.
 */
void compute_occurrence_array(int occurrence_array[ASCII_CHARACTER_SET_SIZE], char* string) {
	int i = 0;
	int count = 0;
	occurrence_array[0] = 0;
    while (*(string + i) != '\0'){
		int str = (int)*(string + i);
		if ( count == 0){
		for ( int i = 1; i < ASCII_CHARACTER_SET_SIZE; i++){
			*(occurrence_array + i) = 0;
		}
		}
		*(occurrence_array +str) = *(occurrence_array +str) + 1;
		
		i = i + 1;
		count = count + 1;
	}
}

/**
 * Given an integer array of size ASCII_CHARACTER_SET_SIZE, this function
 * computes and returns the number of characters that occur one or more times.
 *
 * @param occurrence_array An array representing the occurrences of ASCII
 * characters. The array size should be ASCII_CHARACTER_SET_SIZE.
 * @return The number of characters occurring one or more times in the ASCII
 * character set.
 */
int count_positive_occurrences(int occurrence_array[ASCII_CHARACTER_SET_SIZE]) {
	 int count = 0;
    for (int i = 1; i < ASCII_CHARACTER_SET_SIZE; i++) {
        if (occurrence_array[i] > 0) {
            count++;
        }
    }
    return count;
}

/**
 * Given an integer array of size ASCII_CHARACTER_SET_SIZE, representing the
 * number of occurrences of ASCII characters, this function creates and returns
 * a sorted linked list of WackyLinkedNodes.
 *
 * Each node in the list stores a tree with a single leaf node. The node will
 * contain information about the probability of occurrence 'weight' and the
 * ASCII character itself 'val'.
 *
 * @note Exclude elements with a probability of 0 from the linked list.
 * @note Ensure that the linked list is sorted in ascending order from head to
 * tail, first by the probability of occurrence ('weight'), and in case of ties,
 * by the ASCII character ('val') in ascending order.
 * @note Compute the probability of occurrence for each ASCII character α as
 * occurrence_array[α] / SUM(occurrence_array).
 * @note The memory of any required data types must be allocated manually.
 *
 * @param occurrence_array An array representing the occurrences of ASCII
 * characters. The array size should be ASCII_CHARACTER_SET_SIZE.
 * @return A pointer to the head of the created linked list of WackyLinkedNodes.
 */
void insertingnode(WackyLinkedNode** header, WackyLinkedNode* newn) {
    WackyLinkedNode* curr1 = *header;
    WackyLinkedNode* prev1 = NULL;
    while (curr1 != NULL && (curr1->val->weight < newn->val->weight || (curr1->val->weight == newn->val->weight && curr1->val->val < newn->val->val))) {
        prev1 = curr1;
        curr1 = curr1->next;
    }
	if (prev1 == NULL) {
        newn->next = *header;
        *header = newn;
    } else {
        newn->next = curr1;
        prev1->next = newn;
    }
}

WackyLinkedNode* create_wacky_list(int occurrence_array[ASCII_CHARACTER_SET_SIZE]) {
	WackyLinkedNode* header = NULL;
	for ( int i = 0; i < ASCII_CHARACTER_SET_SIZE; i++){
		double prob = (double)occurrence_array[i] / sum_array_elements(occurrence_array, ASCII_CHARACTER_SET_SIZE);
		if (prob != 0) {
			char vals = (char)i;
			WackyTreeNode* leaf = new_leaf_node(prob, vals);
			WackyLinkedNode* newNode = new_linked_node(leaf);

			insertingnode(&header, newNode);
        }
    }

    return header;
}

/**
 * Given a sorted linked list of WackyTreeNodes, where each node (initially)
 * contains a tree with a single leaf node, this function generates a tree based
 * on the following algorithm:
 * - If the size of the linked list is 2 or more:
 *    - Remove 2 WackyLinkedNodes from the head.
 *    - Create a new WackyTreeNode that joins the tree nodes inside the removed
 *      linked nodes. The first node ('head') goes to the LEFT, and the
 *      following node ('head->next') goes to the RIGHT.
 *    - Create a new WackyLinkedNode and add the newly created WackyTreeNode
 *      back into the linked list. The linked list must remain in sorted order
 *      by the probability of occurrence 'weight'. If the newly created node has
 *      the same weight as another node already in the list, add it in front of
 *      all existing similarily weighted nodes.
 *    - Repeat this algorithm until the size of the linked list is 1.
 * - If the size of the linked list is 1:
 *    - Return the address of the tree held at the head of the linked list.
 * - Otherwise:
 *    - Return NULL.
 *
 * @note The memory of any WackyLinkedNodes must be freed by the end of this
 * function.
 *
 * @param linked_list The sorted linked list of WackyTreeNodes.
 * @return A pointer to the root of the generated tree or NULL if the list is
 * empty.
 */
void sortlistbst(WackyLinkedNode** linked_list, WackyLinkedNode* newlinnode, WackyTreeNode* newtree1) {
    if (*linked_list == NULL || newtree1->weight < (*linked_list)->val->weight) {
        newlinnode->next = *linked_list;
        *linked_list = newlinnode;
    } else {
        WackyLinkedNode* present = *linked_list;
        while (present->next != NULL && present->next->val->weight < newtree1->weight) {
            present = present->next;
        }
        newlinnode->next = present->next;
        present->next = newlinnode;
    }
}

WackyTreeNode* merge_wacky_list(WackyLinkedNode* linked_list) {
    WackyTreeNode* res = NULL;
	while (linked_list != NULL && linked_list->next != NULL) {
        WackyLinkedNode* prev2 = linked_list;
        WackyLinkedNode* curr2 = linked_list->next;
        linked_list = linked_list->next->next;
        WackyTreeNode* newtreee = new_branch_node(prev2->val, curr2->val);
        free(prev2);
        free(curr2);
        WackyLinkedNode* linkednode1 = new_linked_node(newtreee);
        sortlistbst(&linked_list, linkednode1, newtreee);
    }

    if (linked_list != NULL) {
        res = linked_list->val;
        free(linked_list);
    }

    return res;
}

/**
 * Given a tree, this function calculates and returns the height of the tree.
 *
 * @note An empty tree (NULL) has a height of 0.
 *
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int get_height(WackyTreeNode* tree) {
    if (tree == NULL){
		return 0;
	}
	int h;
	int left = get_height(tree->left);
	int right = get_height(tree->right);
	return h = MAX(left,right) + 1;
}

/**
* Given a WackyTree and a specific character, this function computes the
* traversal of the character based on its position in the tree. Movement to the
* LEFT is FALSE, and movement to the RIGHT is TRUE. The steps are written
* inside boolean_array, and the total number of steps is stored in array_size.
*
* @note the size of boolean_array is greater than or equal to get_height(tree)
*
* @param tree Pointer to the root of the WackyTree.
* @param character The specific ASCII character to compute the encoding for.
* @param boolean_array An array to store the traversal steps.
* @param array_size Pointer to the variable holding the total number of steps.
* If the character is not found, -1 is written to array_size instead.
*/
void searchchar(WackyTreeNode* wtree, char char1, bool bool_arr[], int* array_size, int depth1);
void searchleft(WackyTreeNode* tree, char char2, bool boolean_array[], int* array_size, int depth2) {
    if (tree->left != NULL) {
        boolean_array[depth2] = false;
        searchchar(tree->left, char2, boolean_array, array_size, depth2 + 1);
        if (*array_size != -1) {
            return;
        }
    }
}
void searchrit(WackyTreeNode* tree, char char3, bool boolean_array[], int* array_size, int depth3) {
    if (tree->right != NULL) {
        boolean_array[depth3] = true;
        searchchar(tree->right, char3, boolean_array, array_size, depth3 + 1);
        if (*array_size != -1) {
            return;
        }
    }
}
void searchchar(WackyTreeNode* tree1, char char1, bool boolean_array[], int* array_size, int depth1) {
    if (tree1 == NULL) {
        *array_size = -1;
        return;
    }

    if (tree1->val == char1) {
        *array_size = depth1; // Set array size to the depth of the node
        return;
    }

    searchleft(tree1, char1, boolean_array, array_size, depth1);
    if (*array_size != -1) {
        return;
    }

    searchrit(tree1, char1, boolean_array, array_size, depth1);
}

void get_wacky_code(WackyTreeNode* tree, char character, bool boolean_array[], int* array_size) {
    *array_size = -1;
    searchchar(tree, character, boolean_array, array_size, 0);
}


/**
 * Given the root of a WackyTree, a boolean array, and the size of the array,
 * this function traverses the tree. FALSE indicates a movement to the left,
 * and TRUE indicates a movement to the right. The function returns the
 * character at the node reached after all the steps have been taken. If the
 * node is not a leaf node (LEFT and RIGHT are NOT NULL), it returns the
 * DELIMITER ('\0') instead.
 *
 * @param tree Pointer to the root of the WackyTree.
 * @param boolean_array An array representing the traversal steps.
 * @param array_size The size of the boolean array.
 * @return The character at the reached node or the DELIMITER ('\0') if the node
 * is not a leaf node.
 */
char get_character(WackyTreeNode* tree, bool boolean_array[], int array_size) {
	WackyTreeNode* head1 = tree;
	if (tree == NULL && array_size <= 0){
		return '\0';
	}
    for (int i = 0; i < array_size; i++){
		if (boolean_array[i] == true){
			if (head1->right != NULL){
				head1 = head1->right;
			}else{
				return '\0';
			}
		}
		else if (boolean_array[i] == false){
			if (head1->left != NULL){
				head1 = head1->left;
			}
			else{
				return '\0';
			}
		}
	}			
    return head1->val;
}

/**
 * Given a binary tree, this function frees the memory associated with the
 * entire tree.
 *
 * @param tree Pointer to the root of the binary tree to be freed.
 */
void free_tree(WackyTreeNode* tree) {
    if (tree == NULL) {
        return;
    }

    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}
