
class stack						//ջ��
{
	public:
		stack();
		~stack();
		void clearstack();		//���
		bool isempty();			//�п�
		int length();			//�󳤶�
		char gettop();			//ȡջ��Ԫ��
		int push(char);			//�ַ���ջ
		char pop();				//��ջ
		void traverse();		//����
	protected:
		char *base;				//ջ��ָ��
		char *top;				//ջ��ָ��
};