使用dummynode可以有效的防止链表的头指针相关问题
链表题中经常会遇到这样的问题：链表的第一个node，因为没有前驱节点，所以该node需要特殊处理，
会导致额外的代码量。如果创建一个dummy，将其作为第一个node的前驱节点，这样链表中所有的node都可以也能够同样的逻辑来处理了。
class Solution{
public:
    ListNode* deleteDuplicates(ListNode* head){
        if(head==nullptr)return nullptr;

        ListNode* dummy =new ListNode(0);
        dummy->next = head;
        ListNode* node = dummy;
        while (node->next != nullptr && node->next->next != nullptr)
        {
            if(node->next-val == node->next->next->val){
                int val_prev = node->next->val;
                while (node->next != nullptr && val_prev == node->next->val)
                {
                    ListNode* temp = node->next;
                    node->next = node->next->next;
                    delete temp;
                }
                
            }else{
                node= node->next;
            }
        }
        return dummy->next;
    }
};