#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

	int num;//ѧ��
	char name[16]; 	//����
	char sex[6];	//�Ա�
	int age;	//����
	char birth[15];//�����1998��12��21�գ��������ְ˸����֣�3*2+8+1=15
	char phone[23];//�ֻ���
	char email[101];//��������
	char adrs[101];//���50������*2�ֽ�/����=100�ֽڣ��ټ�һ��'\0'��β����һ����101�ֽ�
	struct _Stu *next;
} Stu;

/*���������б�*/

//�˵�����
void menu(void);

//���ļ�������Ϣ�������ı�ȫ��ͷָ��ph
int readf(void);

//����ָ����ָ��ʾĳ����Ϣ
void pri(Stu *p);

//��ʾ������Ϣ pri��������
void display(Stu *head);

//�½���������ļ�����
int create(void);

//�õ��ض�ѧ�ŵĽṹ��ָ��
Stu *seeint(int num);

//�õ��ض������Ľṹ��ָ��
Stu *seechar(char *nam);

//����ѧ�š�������ѯѧ����Ϣ�������ظ�ѧ��ѧ�ţ�seechar() seeint() ��������
int search(void);

//����search()���ص�ѧ��,��ͨ��seeint()�ҵ�ָ�룬�޸���Ϣ
int modify(void);

//ɾ������
int del(void);

//����
int sort();

//�ļ�����
int savef();

Stu *ph = NULL;


int main()
{
	ph = NULL;
	if (readf()) {
		printf("�ļ���ʼ���ɹ�,��ӭʹ��!\n\n\n\n");
	} else {
		printf("\n���ڱ���������Ŀ¼�½�studata.txt�������!\n\n\n\n");
		getchar();
		return 0;
	}

	do {
		int choice;
		menu();
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				system("cls");
				printf("\n=====�������ѧ����Ϣ=====\n");
				if (ph==NULL) {
					printf("ѧ����ϢΪ�գ��뷵�����˵��½���Ϣ\n");
				} else {
					display(ph);
				}
				break;
			case 2:
				system("cls");
				printf("\n=====�½�ѧ����Ϣ=====\n");
				if(create()) {
					printf("��Ϣ�ɹ�����\n");
				} else {
					printf("��Ϣ�������\n");
				}
				break;
			case 3:
				system("cls");
				printf("\n=====��ѯѧ����Ϣ=====\n");
				search();
				break;
			case 4:
				system("cls");
				printf("\n=====�޸�ѧ����Ϣ=====\n");
				if(modify())break;
			case 5:
				system("cls");
				printf("\n=====ɾ��ѧ����Ϣ=====\n");
				if(del()) {
					printf("\nɾ���ɹ���\n");
					break;
				} else { //bug
					printf("\n�޴�ѧ����Ϣ��\n");
					break;
				}
			case 6:
				system("cls");
				printf("\n=====��ѧ����������=====\n");
				if(sort()) {
					printf("ð������ɹ���\n");
				} else {
					printf("������С��2���޷�����ð������");
				}
				break;
			case 0:
				system("cls");
				printf("\n=====����ѧ����Ϣ=====\n\n");
				if(savef()) {
					printf("����ɹ�\n\n");
				} else {
					printf("����ʧ��\n\n");
				}
				printf("��ӭ�´�ʹ��,�ټ�!\n");
				if (!ph) {	//�ͷ��ڴ�
					free(ph);
				}
				printf("\n�������������\n");
				getch();
				return 0;

			default:
				system("cls");
				printf("\n�������,������ѡ�����!\n");
				break;
		}

		while(1) {
			printf("\n��������ɷ������˵���\n");
			if(getch()) break;
		}
		system("cls");
	} while(1);

}

//�˵�
void menu()
{
	printf("************************************************\n");
	printf("*************���칤ѧ����Ϣ����ϵͳ*************\n");
	printf("************************************************\n\n");
	printf("\n\n��ѡ�����:\n\n");
	printf("1.���ѧ����Ϣ.\n");
	printf("2.�½�ѧ����Ϣ.\n");
	printf("3.��ѯѧ����Ϣ.\n");
	printf("4.�޸�ѧ����Ϣ.\n");
	printf("5.ɾ��ѧ����Ϣ.\n");
	printf("6.��ѧ����������.\n");
	printf("0.�˳���������Ϣ.\n");
	printf("\n  ���ѡ���ǣ�");
}





//���ļ�������Ϣ�������ı�ȫ��ͷָ��ph
int readf()
{
	FILE *pf;
	Stu *p,*tail;
	pf = fopen("studata.txt", "r");
	if(!pf) {
		return 0; //ʧ�ܺ���ִ�����²���
	}
	fgetc(pf);//ָ����λ
	while(!feof(pf)) {
		p = (Stu *)malloc(sizeof(Stu));
		fscanf(pf,"%d%s%s%d%s%s%s%s",&p->num, p->name,p->sex ,&p->age,
		       p->birth,p->phone, p->email,p->adrs);
		//������Ϣ
		if(ph == NULL) {
			ph = p;
			tail = p;
		} else {
			tail->next = p;
			tail = p;
		}
		fgetc(pf);
		fgetc(pf);
		if(feof(pf)) {
			tail->next=NULL;
		}
	}
	if(!pf) {
		fclose(pf);//�ر��ļ�

	}
	return 1;//�ɹ�
}

//����ָ����ʾĳ����Ϣ
void pri(Stu *p)
{
	if(p) {
		printf("ѧ��:%d\t����:%s\t�Ա�:%s\t����:%d\t��������:%s\t�绰:%s\t�����ʼ�:%s\t��ַ:%s\t\n",
		       p->num, p->name,p->sex,p->age,p->birth,p->phone, p->email,p->adrs);
	} else {
		printf("������Ϣ��Ч");
	}
	return;
}


//��ʾ������Ϣ pri��������
void display(Stu *head)
{
	Stu *p;
	p = head;//���ı䴫��ָ���ֵ
	while(1) {
		pri(p);
		if(p->next) {
			p = p->next;
		} else {
			break;
		}

	}
	return;
}

//�õ��ض�ѧ�ŵĽṹ��ָ��
Stu *seeint(int num)
{
	Stu *p;
	p = ph;
	while (p && (p->num != num)) {
		p = p->next;
	}
	return p;
}

//�õ��ض�ѧ�ŵĽṹ��ָ��
Stu *seechar(char *nam)
{
	Stu *p;
	p = ph;
	while(p && strcmp(nam,p->name)) {
		p = p->next;
	}
	return p;
}



int create()
{
	Stu *p,*head,*tail;//��ʱ����ָ�롢ͷָ�롢βָ��
	int a=1;
	head = NULL;
	do {
		p = (Stu *)malloc(sizeof(Stu));
		printf("\n������ѧ�ţ��칤ѧ��Ϊ11λ��:");
		scanf("%d", &p->num);
		//�жϸü�¼�Ƿ����
		if (seeint(p->num)) {
			printf("ѧ��Ϊ%d�ļ�¼�Ѵ���!\n",p->num);
			return 0;
		}
		printf("����������:");
		scanf("%s",p->name);
		printf("�������Ա��л�Ů��:");
		scanf("%s",p->sex);
		printf("����������:");
		scanf("%d", &p->age);
		printf("������������£�����1998��12��21�գ�:");
		scanf("%s",p->birth);
		printf("������绰:");
		scanf("%s",p->phone);
		printf("����������ʼ���ַ:");
		scanf("%s",p->email);
		printf("�������ַ:");
		scanf("%s",p->adrs);
		if(head == NULL) {
			head = p;
			tail = p;
		} else {
			tail->next = p;
			tail = p;
		}
		tail->next=NULL ;
		printf("\n����0�س���ֹ����������ֵ�س�����\n");
		scanf("%d", &a);
	} while(a!=0);
	//����ph��head��״̬����������
	if(head) {
		if(ph) {
			tail->next=ph;
			ph=head;
			return 1;//ph��head����Ϊ��ʱ���ӣ�����1
		} else {
			ph=head;
			return 1;//phΪ�ա�head��Ϊ��ʱ��ֵ������1
		}
	} else {
		return 0;//ph��headΪ��ʱ����0��ph���ա�headΪ��ʱ����0
	}
}




//����ѧ�š�������ѯѧ����Ϣ�������ظ�ѧ��ѧ��  seechar seeint ��������
int search()
{
	Stu *p;
	int m=0, n;
	char nam[16];
	while(m!=1&&m!=2) {
		printf("\n\n��������Լ�����\n1.��ѧ�Ų���\n2.����������\n");
		scanf("%d", &m);
	}
	if(m==1) {
		printf("������Ҫ��ѯ��ѧ��:");
		scanf("%d", &n);
		if(seeint(n)) {
			pri(seeint(n));
		} else {
			printf("���޴���");
		}
	}
	if(m==2) {
		printf("������Ҫ��ѯ������:");
		scanf("%s",nam);
		if(seechar(nam)) {
			pri(seechar(nam));
		} else {
			printf("���޴���");
		}
	}/*Ϊ����modify��׼�� */
	if(seeint(n)) {
		p=seeint(n);
		return p->num;
	}
	if(seechar(nam)) {
		p=seechar(nam);
		return p->num;
	}
}


int modify()
{
	int choice; //�û�ѡ�����
	Stu *p=seeint(search());
	if (p == NULL) {
		printf("�����ڴ�ѧ�ŵļ�¼!\n");
		return 1;
	}
	printf("0.�޸�ѧ��.\n");
	printf("1.�޸�����.\n");
	printf("2.�޸��Ա�.\n");
	printf("3.�޸�����.\n");
	printf("4.�޸ĳ�������.\n");
	printf("5.�޸ĵ绰.\n");
	printf("6.�޸ĵ����ʼ���ַ:.\n");
	printf("7.�޸ĵ�ַ.\n");
	printf("��ѡ��Ҫ�޸ĵ���Ϣ:");
	scanf("%d", &choice);
	switch (choice) {
		case 0:
			printf("������ѧ��:");
			scanf("%d",&p->num);
			break;
		case 1:
			printf("����������:");
			scanf("%s",p->name);
			break;
		case 2:
			printf("�������Ա��л�Ů��:");
			scanf("%s",p->sex);
			break;
		case 3:
			printf("����������:");
			scanf("%d", &p->age);
			break;
		case 4:
			printf("������������£�����1998��12��21�գ�:");
			scanf("%s",p->birth);
			break;
		case 5:
			printf("������绰:");
			scanf("%s",p->phone);
			break;
		case 6:
			printf("����������ʼ���ַ:");
			scanf("%s",p->email);
			break;
		case 7:
			printf("�������ַ:");
			scanf("%s",p->adrs);
			break;
		default:
			printf("�������������ѡ�����!\n");
	}
	return 1;
}

int del()
{
	Stu *see,*p,*pre;//pΪ��Ӧѧ�ŵ�ָ�룬pre�Ƕ�Ӧѧ�ŵ�ǰһ����ָ��
	int num;
	printf("������Ҫɾ����Ϣ��ѧ��:\n");
	scanf("%d", &num);
	if(!seeint(num)) {
		return 0;
	}
	p = ph;//��ͷ��ʼ����
	if(!p) return 0;//����Ϊ�����˳�
	//��һ��ΪҪɾ������ɾ������
	if(p->num==num) {
		if(!p->next) {
			ph=NULL;
			free(p);
			return 1;
		} else {
			ph=p->next;
			free(p);
			return 1;
		}
	}
	//�ڶ����Լ�֮��ΪҪɾ������ɾ������
	while(p->num!=num) {
		pre=p;
		p=p->next;
	}
	pre->next=p->next;
	free(p);
	return 1;
}

int sort()
{
	Stu *c=ph,*head,*prr,*pre,*p,*temp;
	int n,count,i;
	while(c) {
		count++;
		c=c->next;
	}
	if(count<=1) {
		return 0;
	}//�����������ż���
	head=(Stu*)malloc(sizeof(Stu));
	head->next=ph;//�������ͷ���ӿս��
	n=count*(count-1)/2;//��������������
	for(i=1; i<=n; i++) {
		prr=head;//prr���ڵ�һ����� ��Ϊ�գ�
		pre=head->next;	//pre���ڵڶ������
		p=head->next->next;//p���ڵ��������
		while(1) {
			//�Ƚ�pre��ָ��p��ָ�Ĵ�С����������
			if((pre->num)>(p->num)) {
				temp=p->next;
				prr->next=p;
				p->next=pre;
				pre->next=temp;
				//�ص�ԭ����˳��
				temp=pre;
				pre=p;
				p=temp;
			}

			//����ָ����λ
			if(!p->next) break;//�����һ���������ֹ
			p=p->next;
			pre=pre->next;
			prr=prr->next;
		}

	}
	ph=head->next;//ɾ���ս��
	free(head);
	printf("���������Ϊ%d,\n",count);
	return 1;
}


//���ڴ��е���Ϣ�����ļ�
int savef()
{
	FILE *pf;
	Stu *p;
	pf = fopen("studata.txt", "w");
	if(!pf) {
		return 0; //ʧ�ܺ���ִ������
	}
	p=ph;//��ͷ��ʼ
	while (p) {
		fprintf(pf," %d\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t",p->num, p->name,
		        p->sex , p->age, p->birth,p->phone, p->email,p->adrs);
		p=p->next;
	}
	if(!pf) {
		fclose(pf);
	}
	return 1;
}


