﻿#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Functions.h"
using namespace std;
PostMan* postman[100];
Client* client[100];
Goods* goods[100];
Box* box[100];
Keys keys;

void getPostMan()
{
	string a, b, c, e, f;
	int d;
	fstream fio("D:\\postman.txt", ios::in | ios::out);
	if (fio.is_open())
	{
		for (int i = 0; i < 100; i++)
		{
			if (fio.eof())
				break;
			fio >> a >> b >> c >> d >> e >> f;
			postman[i] = new PostMan(a, b, c, d, e, f);
		}
		fio.close();
	}
	else
		cout << "文件postman打开失败." << endl;
}

void getClient()
{
	string a, b, c, d;
	int e;
	fstream fio("D:\\client.txt", ios::in | ios::out);
	if (fio.is_open())
	{
		for (int i = 0; i < 100; i++)
		{
			if (fio.eof())
				break;
			fio >> a >> b >> c >> d >> e;
			client[i] = new Client(a, b, c, d, e);
		}
		fio.close();
	}
	else
		cout << "文件client打开失败" << endl;
}

void getGoods()
{
	string a, b;
	int c, d;
	fstream fio("D:\\goods.txt", ios::in | ios::out);
	if (fio.is_open())
	{
		for (int i = 0; i < 100; i++)
		{
			if (fio.eof())
				break;
			fio >> a >> b >> c >> d;
			goods[i] = new Goods(a, b, c, d);
		}
		fio.close();
	}
	else
		cout << "文件goods打开失败" << endl;
}

void getKeycell() {
	string a;
	long long b;
	int c, d;
	ifstream fr;
	fr.open("D:\\key.txt", ios::in);
	if (fr.is_open()) {
		while (1) 
		{
			fr >> a;
			if (fr.eof())
				break;
			fr >> b >> c >> d;
			keys.insertKey(new Keycell(a, b, c, d));
			box[c]->putBox(d);
		}
		fr.close();
	}
	else
		cout << "文件key打开失败" << endl;
}

void savePostman() {
	ofstream fw;
	fw.open("D:\\postman.txt", ios::out);
	if (fw.is_open()) {
		for (int i = 0; postman[i] != NULL; i++) {
			if (i != 0)
				fw << endl;
			fw << postman[i]->getId() << "\t"
				<< postman[i]->getTel() << "\t"
				<< postman[i]->getName() << "\t"
				<< postman[i]->getPostId() << "\t"
				<< postman[i]->getPosition() << "\t"
				<< postman[i]->getPassWord();
		}
		fw.close();
	}
	else
		cout << "文件postman打开失败" << endl;
}

void saveClient() {
	ofstream fw;
	fw.open("D:\\client.txt", ios::out);
	if (fw.is_open()) {
		for (int i = 0; client[i] != NULL; i++) {
			if (i != 0)
				fw << endl;
			fw << client[i]->getId() << "\t"
				<< client[i]->getTel() << "\t"
				<< client[i]->getName() << "\t"
				<< client[i]->getAddress() << "\t"
				<< client[i]->getClintId();
		}
		fw.close();
	}
	else
		cout << "文件client打开失败" << endl;
}

void saveGood() {
	ofstream fw;
	fw.open("D:\\goods.txt", ios::out);
	if (fw.is_open()) {
		for (int i = 0; goods[i] != NULL; i++) {
			if (i != 0)
				fw << endl;
			fw << goods[i]->getpName() << "\t"
				<< goods[i]->getrName() << "\t"
				<< goods[i]->getStation() << "\t"
				<< goods[i]->getGoodsId();
		}
		fw.close();
	}
	else
		cout << "文件goods打开失败" << endl;
}

void saveKey() {
	ofstream fw;
	int i = 0;
	fw.open("D:\\key.txt", ios::out);
	if (fw.is_open()) {
		Keycell *p=keys.head;
		p=p->next;
		while (p != NULL)
		{
			if (i != 0)
				fw << endl;
			fw << p->getKey() << ' ' << p->getGoodsId() << ' ' << p->getBoxId() << ' ' << p->index;
			p=p->next;
			i++;
		}
		fw.close();
	}
	else
		cout << "文件key打开失败" << endl;
}

void creatNewPostman() {
	string id1;// 身份证号
	string tel1;// 电话
	string name1;// 姓名
	int postId1;//工号
	string position1;//职位
	string passWord1;//密码
	int tt = 1;//第几位快递员

	cout << "请准确输入身份证号码：";
	cin >> id1;
	cout << "\n" << "请输入手机号码：";
	cin >> tel1;
	cout << "\n" << "请输入姓名：";
	cin >> name1;
	cout << "\n" << "请输入工号：";
	cin >> postId1;
	cout << "\n" << "请设置职位：";
	cin >> position1;
	cout << "\n" << "请设置密码：";
	cin >> passWord1;
	for (int i = 0; postman[i] != NULL; i++) {
		if (postman[i]->getId() == id1 || postman[i]->getTel() == tel1 || postman[i]->getPostId() == postId1) {
			cout << "和已有信息重复，请核对信息后再尝试！" << endl;
			return;
		}
	}
	cout << "已成功注册" << endl;
	for (int i = 0; postman[i] != NULL; i++) {
		tt = i;
	}
	postman[tt+1] = new PostMan(id1, tel1, name1, postId1, position1, passWord1);
	savePostman();
}

void createGoods() {
	string pId1;//寄件人clintid
	string rId1;//收件人clintid
	long long goodsId1=0;
	int i, j;
	cout << "请输入寄件人（id）：";
	cin >> pId1;
	cout << "\n请输入收件人（id）:";
	cin >> rId1;
	int record1 = 1;//记录寄件人是否存在
	int record2 = 1;//记录收件人是否存在
	int record3 = 1;//记录快递是否存在
	for (i = 0; client[i] != NULL; i++) {
		if (client[i]->getId() == pId1) {
			record1 = -1;
			break;
		}
	}
	for (j = 0; client[j] != NULL; j++) {
		if (client[j]->getId() == rId1) {
			record2 = -1;
			break;
		}
	}

	for (i = 0; goods[i] != NULL; i++) {
	}
	goodsId1 = (long long)i;

	if (record1 == -1 && record2 == -1)
	{
		goods[i] = new Goods(pId1, rId1, 0, goodsId1);
		saveGood();
		cout << "新建包裹成功" << endl;
		system("pause");
	}
	else
		cout << "包裹信息错误，请检查后重试";
}

void initial()
{
	box[0] = new Box(1, 2);//快递柜
	box[1] = new Box(2, 2);//设置快递柜数量为2个
	getPostMan();
	getClient();
	getGoods();
	getKeycell();
}

void Put()
{
	//输入用户名和密码，略
	int boxId;
	int freeIndex;
	long long goodsId;
	cout << "输入当前快递柜编号" << endl;
	cin >> boxId;
	if (boxId > 1 || boxId < 0)
	{
		cout << "输入错误" << endl;
		return;
	}
	freeIndex = box[boxId]->getFreeBox();
	if (freeIndex == -1)
	{
		cout << "此柜已满，请换一个" << endl;
		return;
	}
	box[boxId]->printBox(freeIndex);
	cout << "请输入要放入的快递编号." << endl;
	cin >> goodsId;
	
	if (goods[goodsId]==NULL||goods[goodsId]->getStation() != 0)
	{
		cout << "此快递已放入或已取出，请重新输入" << endl;
		return;
	}
	goods[goodsId]->putGoods();
	box[boxId]->putBox(freeIndex);
	Keycell* temp = new Keycell("", goodsId, boxId, freeIndex);
	temp->setRandomKey();
	keys.insertKey(temp);
	cout << "已成功存入." << endl;
	temp->sendMessage();
	saveGood();
	saveKey();

	return;
}

void Check()
{
	string key;
	Keycell temp;
	cout << "请输入密码" << endl;
	cin >> key;
	temp = keys.findKey(key);
	if (temp.getKey() == "")
	{
		cout << "输入错误，不存在此密码，请检查是否输入错误" << endl;
		return;
	}
	box[temp.getBoxId()]->checkBox(temp.index);
	goods[temp.getGoodsId()]->checkGoods();
	cout << "取件成功" << endl;
	saveGood();
	saveKey();
}

void checkBox()
{
	int boxId;
	cout << endl;
	cout << "\t\t\t\t\t ----------------------------" << endl;
	cout << "\t\t\t\t\t|*****输入当前快递柜编号*****|" << endl;
	cout << "\t\t\t\t\t\t\t";
	cin >> boxId;
	if (boxId > 1 || boxId < 0)
	{
		cout << "\t\t\t\t\t\t|*输入错误*\t|" << endl;
		return;
	}
	cout << "\t\t\t\t\t|*****快递柜使用情况如下*****|" << endl;
	cout << "\t\t\t\t\t ----------------------------" << endl;
	box[boxId]->printBoxStation();
	return;
}

void checkGoods()
{
	int goodsId;
	cout << "请输入快递编号" << endl;
	cin >> goodsId;
	if (goods[goodsId] == NULL)
	{
		cout << "没有这个快递!" << endl;
		return;
	}
	if (goods[goodsId]->getStation() == 2)
	{
		time_t seconds;

		seconds = time(NULL);
		long long a = seconds;
		cout << "编号为" << goodsId
			<< "的快递已经在" << a - goods[goodsId]->getChecktime()
			<< "秒前被取走" << endl;
		return;
	}
	else if (goods[goodsId]->getStation() == 1)
	{
		keys.findGoods(goodsId);
		return;
	}
	else
	{
		cout << "此快递并未到达快递柜" << endl;
		return;
	}
}

void checkOvertime()
{
	int record = 1;
	int i;
	time_t seconds;
	seconds = time(NULL);
	long long a = seconds;
	cout << "超时快递：" << endl;
	for (i = 0; i < 100; i++) {
		if (goods[i] == NULL)//
			break;
		if (goods[i]->getStation() == 1 && a - goods[i]->getPuttime() >= 10)//10s即过期
		{
			keys.findGoods(goods[i]->getGoodsId());
			record = 0;
		}
	}
	if (record)
		cout << "不存在超时快递" << endl;
}
