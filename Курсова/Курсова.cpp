#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <direct.h>
#include <process.h>

using namespace std;

const int MAX_ARGUMENTS = 10;
const int commandsCount = 10;

void attrib();
void ukr();
void help();
void cls();
void ar();
void hdd();
void ls();
void move();
void date();
void view();

void attribHelp()
{
	cout << "attrib �������� i ��i��� �������� �����.\n";
	cout << "������ �������: attrib FILENAME (-x), �� FILENAME - ����� �����, -x - ������������ ��������\n";
	cout << "��������: \n-h - ����������;\n-n - ����������;\n-a - ���i�;\n-r - ���� ��� �������;\n-s - ���������;\n-t - ����������;\n";
	cout << "��� ������ �������i�, ����i�� -n.\n";
	cout << "����� ������������� ���i���� ���������, ������������� ����� ������. ���������: attrib file.txt -h -r\n";
}
void ukrHelp()
{
	cout << "������� �����i� :)!\n";
	cout << "������ ����i���� :)\n";
}
void exitHelp()
{
	cout <<"exit ������� ��������.\n";
}
void clsHelp()
{
	cout<<"cls �������� ������.\n";
}
void dateHelp()
{
	cout<<"cls �������� ������.\n";
}
void helpHelp()
{
	cout <<"���i� i�������i� ��� ��������.\n";
}
void lsHelp()
{
	cout<<"ls �������� ��������� ��������.\n";
}
void hddHelp()
{
	cout<<"HDD ��������� �i������ �i��� �� �i�������i.\n";
	cout<<"������ �������: hdd X:\, �� X:\ - ����� �����\n";
}
void viewHelp()
{
	cout<<"HDD ��������� �i������ �i��� �� �i�������i.\n";
	cout<<"������ �������: hdd X:\, �� X:\ - ����� �����\n";
}
void arHelp()
{
	cout << "ar - ���i������� �����.\n";
	cout << "������ ����� �������: ar x rar.rar FILENAME\n";
	cout << "�� x - ����� ���i�������:\n� - ���i������ ����\n� - ������i������ ����\nd - ��������� ���i��.\n";
	cout << "rar.rar - ����� ���i��.\n";
	cout << "FILENAME - ����� �����.\n";
	cout << "������� ���i����� ���i����� ����i�. �������: ar a RAR.rar file1.txt file2.txt\n";
}
void moveHelp()
{
	cout << "�����i� ��������� move\n";
	cout << "������ ����� �������:\n";
	cout << "move PATH1 PATH2\n,�� PATH1 - ��������i� �����,\nPATH2 - ���� ����������.\n";
}

struct
{	char commandName[255];
	char** arguments;
	int argcount;
	void (*help)();
	void (*exec)();
}command;

typedef struct
{	char commandName[255];
	void (*help)();
	void (*exec)();
} CommandDef;

const CommandDef commandsAvail[] = {{"view",viewHelp,view},{"exit",exitHelp,NULL},{"date",dateHelp,date},{"attrib",attribHelp,attrib},{"cls",clsHelp,cls},{"help",helpHelp,help},{"hdd",hddHelp,hdd},{"ar",arHelp,ar},{"ls",lsHelp,ls},{"ukr",ukrHelp,ukr},{"move",moveHelp,move}};

void dispatchCommand()
{
	for (int i=0;i<commandsCount;i++)
	{
		if (strcmp(command.commandName,commandsAvail[i].commandName)==0)
		{
			command.help = commandsAvail[i].help;
			command.exec = commandsAvail[i].exec;
		}
	}
}

void help()
{
	cout<<"\n�������� �������� ��������� ����� 1�I-12(�) ���������� ������\n";
	cout<<"�����i� ������:\n";
	cout<<"ar - ���i������� �����\n";
	cout<<"attrib - ���i� i ������������ �������i� �����\n";
	cout<<"hdd - ���i� �i������(���������) �i��� �� �i�������i\n";
	cout<<"ls - ��i�� ����������� ��������\n";
	cout<<"ukr - ����� :)\n";
}

void ukr()
{
	cout << "����� ����i�i!\n";
	cout << "������ �����!\n";
}

void move()
{
	if(command.argcount == 2)
	{
		MoveFile(command.arguments[0],command.arguments[1]);
	}
	else cout<<"������������ ��i� �������";
}

void view()
{
	ShellExecute(NULL,"open",command.arguments[0],NULL,NULL,SW_SHOWNORMAL);
}


void date()
{
	SYSTEMTIME st;
	if (command.arguments[0] && strcmp(command.arguments[0],"change")==0)
		//�����i����� �� �������� �� ������ ���� �� ������ �� �������� ������� ���i� �� �����
	{
	GetSystemTime(&st);
	cout <<"������� ����:\n";
	if (st.wDay<10) cout << 0; 
	cout <<st.wDay <<".";//
	if (st.wMonth <10)cout<<0;
	cout<<st.wMonth <<"."<<st.wYear << endl;
	cout <<"����i�� ������� ����:\n";
	char newdate[255];
	cin.getline(newdate,255);
	char *tokenPtr[10];
	int i=0;
	tokenPtr[i]=strtok(newdate,".");
	i++;
	while (tokenPtr[i-1] != NULL)
	{
		tokenPtr[i]=strtok(NULL,".");
		i++;
	}
	i--;
	if (i!=3){cout <<"������ ���� ���i����\n"; return;}
	int day = atoi(tokenPtr[0]);
	if (day < 0 || day > 31) {cout <<"������ ���� ���i����\n"; return;}
	int month = atoi(tokenPtr[1]);
	if (month < 0 || month >12) {cout <<"������ ���� ���i����\n"; return;}
	int year = atoi(tokenPtr[2]);
	if (year < 0){cout <<"������ ���� ���i����\n"; return;}
	SYSTEMTIME newSystemTime;
	GetSystemTime(&newSystemTime);
	newSystemTime.wDay=day;
	newSystemTime.wMonth=month;
	newSystemTime.wYear=year;
	if(!SetSystemTime(&newSystemTime)) //���� ���� �� 
	{
		cout << "������� ������������ ����, ������� �i�����i ����� ���i�i��������\n";
		return;
	}
}
	else
	if (command.arguments[0]==NULL )
	{
	GetSystemTime(&st);
	cout <<"������� ����:\n";
	if (st.wDay<10) cout << 0; 
	cout <<st.wDay <<".";
	if (st.wMonth <10) cout<<0;
	cout<<st.wMonth <<"."<<st.wYear << endl;
	}
	else
	{
		printf("���i��i ���������.���i��� help.\n");
	}
}

void cls()
{
	system("cls");
}

void ar()
{
	if(strcmp(command.arguments[0],"a") == 0)
	{
		for(int i=2;i<command.argcount;i++)
			spawnl(P_WAIT,"WinRAR","WinRAR","","a -std",command.arguments[1],command.arguments[i],NULL);
		cout<<"���i������� ���i���!\n";
	}
	else if (strcmp(command.arguments[0],"e") == 0)
	{
		spawnl(P_WAIT,"WinRAR","WinRAR","","e -std",command.arguments[1],NULL);
		cout<<"������i������� ���i���!\n";
	}
	else if (strcmp(command.arguments[0],"d") == 0)
	{
		spawnl(P_WAIT,"WinRAR","WinRAR","","d -std",command.arguments[1],NULL);
		cout<<"���i� ���������!\n";
	}
	else cout<<"������������ ��������!";
}

void attrib()
{
	if(command.argcount == 0)
	{
		cout<<"Error: �� ������i ��������� ��� �����ii.\n";
	}
	else if (command.argcount == 1)
	{
		WIN32_FIND_DATA sstruct;
		HANDLE hFind = FindFirstFile(command.arguments[0],&sstruct);
		if(hFind!=0)
		{
			cout<<"����������i ��������:\n";
   
				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
				cout<<"����������\n"; 

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)
				cout<<"���������\n";

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
				cout<<"���i����\n";

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED)
				cout<<"������\n";

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				cout<<"�����\n";

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)
				cout<<"����������\n";

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)
				cout<<"�� i�����������\n";
   
				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
				cout<<"���� ��� �������\n";

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)
				cout<<"����������\n";
		}
	}
	  else 
	  {
		  int count = 1;
		  DWORD attributes = 0;
		  while(count<command.argcount)
		  {
			if(strcmp(command.arguments[count],"-h") == 0)
				attributes|=FILE_ATTRIBUTE_HIDDEN;
		
			if(strcmp(command.arguments[count],"-a") == 0)
				attributes|=FILE_ATTRIBUTE_ARCHIVE;
		 
			if(strcmp(command.arguments[count],"-n") == 0)
				attributes|=FILE_ATTRIBUTE_NORMAL;
		 
			if(strcmp(command.arguments[count],"-r") == 0)
			  attributes|=FILE_ATTRIBUTE_READONLY;
		 
			if(strcmp(command.arguments[count],"-s") == 0)
			  attributes|=FILE_ATTRIBUTE_SYSTEM;
		
			if(strcmp(command.arguments[count],"-t") == 0)
			 attributes|=FILE_ATTRIBUTE_TEMPORARY;

			count++;
		  }

		  SetFileAttributes(command.arguments[0],attributes);
	  }
	 }

void hdd()
{
	ULARGE_INTEGER free;
	char NameBuffer[MAX_PATH];
	char SysNameBuffer[MAX_PATH];
	DWORD VSNumber;
	DWORD MCLength;
	DWORD FileSF;
	if (command.argcount == 0) cout<<"�� ������� ��������.\n";
	else
	{
		unsigned int mit = GetDriveType(command.arguments[0]);
		GetVolumeInformation(command.arguments[0],NameBuffer, sizeof(NameBuffer), &VSNumber,
			&MCLength,&FileSF,SysNameBuffer,sizeof(SysNameBuffer));
		GetDiskFreeSpaceEx(command.arguments[0], &free, NULL, NULL);

		if (mit == 0 || mit == 1 || mit == 5)
		{
			cout << "��� �����: ";
			switch(mit)
			{
			case 0:
				cout<<"���� �� ����������.\n";
				break;
			case 1: 
				cout<<"error path.\n";
				break;
			case 5:
				cout<<"CD-ROM.\n";
				break;
			}
		}
		else
		{
		cout << "�i��� ����: " << NameBuffer << endl;
		cout << "������� �������: " << SysNameBuffer << endl;
		cout << "��� �����: ";
		switch(mit)
		{
			case 2:
				cout<<"removable tool.\n";
				break;
			case 3:
				cout<<"�������� ����.\n";
				break;
			case 4:
				cout<<"��������� ����.\n";
				break;
			case 6:
				cout<<"virtual disk.\n";
				break;
		}
		cout << "Free memory " << command.arguments[0] << " " << (double)free.QuadPart/1024/1024/1024<<" Gb\n"; // ��������� ����� � ������
		}
	}
}

void ls()
{
	if (command.argcount != 0)
		cout<<"Error!/n";
	else
		spawnl(P_WAIT,"SLS.exe","SLS.exe",NULL);
}

void commandInput(char* commandLine)
{
	char cmdLine[255];
	strcpy(cmdLine,commandLine);
	char *argsBuffer;
	argsBuffer = strtok(cmdLine," ");
	command.arguments=(char**)calloc(MAX_ARGUMENTS,sizeof(char*));
	if (argsBuffer)
	{
		strcpy(command.commandName,argsBuffer);
		command.argcount=0;
		while (argsBuffer=strtok(NULL," "))
		{
			command.arguments[command.argcount]=(char*)calloc(255,sizeof(char));
			strcpy(command.arguments[command.argcount],argsBuffer);
			command.argcount++;
		}
	}
}

int main(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL,"Russian");
	char consoleInput[255];
	cout<<"�������� ���������� ��������� ����� 1�I-12(�) ���������� ������\n";
	while(strcmp(consoleInput,"exit"))
	{
		char buffer[255];
		if (_getcwd(buffer,254)==NULL)
			perror("Getcwd error");
		else
		{
			cout<<">";
		}
		command.argcount=0;
		command.help=0;
		command.exec=0;
		gets(consoleInput);
		commandInput(consoleInput);
		dispatchCommand();
		if(command.help == NULL)
			cout << "���i���� �������.\n";
		else
		{
			if(command.argcount == 1)
				if (strcmp(command.arguments[0], "/?") == 0)
				{
					if(command.help != NULL)
						(*command.help)(); 
					strcpy(command.commandName," ");
					continue;
				}
					if(command.exec != NULL)
						(*command.exec)();
		}
		strcpy(command.commandName," ");
	}
	return 0;
}