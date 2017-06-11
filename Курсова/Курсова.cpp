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
	cout << "attrib Виводить i змiнює атрибути файла.\n";
	cout << "Формат команди: attrib FILENAME (-x), де FILENAME - назва файлу, -x - встановлення атрибуту\n";
	cout << "Атрибути: \n-h - прихований;\n-n - нормальний;\n-a - архiв;\n-r - лише для читання;\n-s - системний;\n-t - тимчасовий;\n";
	cout << "Для зняття атрибутiв, оберiть -n.\n";
	cout << "Можна встановлювати декiлька параметрів, перераховуючи через пробіли. Наприклад: attrib file.txt -h -r\n";
}
void ukrHelp()
{
	cout << "Бонусна функцiя :)!\n";
	cout << "Будьте патрiотом :)\n";
}
void exitHelp()
{
	cout <<"exit Закриває програму.\n";
}
void clsHelp()
{
	cout<<"cls Очищення екрану.\n";
}
void dateHelp()
{
	cout<<"cls Очищення екрану.\n";
}
void helpHelp()
{
	cout <<"Вивiд iнформацiї про програму.\n";
}
void lsHelp()
{
	cout<<"ls Перегляд поточного каталогу.\n";
}
void hddHelp()
{
	cout<<"HDD Виведення вiльного мiсця на вiнчестерi.\n";
	cout<<"Формат команди: hdd X:\, де X:\ - назва диску\n";
}
void viewHelp()
{
	cout<<"HDD Виведення вiльного мiсця на вiнчестерi.\n";
	cout<<"Формат команди: hdd X:\, де X:\ - назва диску\n";
}
void arHelp()
{
	cout << "ar - Архiвування файлу.\n";
	cout << "Формат вводу команди: ar x rar.rar FILENAME\n";
	cout << "де x - режим архiвування:\nа - архiвувати файл\nе - розархiвувати файл\nd - видалення архiву.\n";
	cout << "rar.rar - назва архiву.\n";
	cout << "FILENAME - назва файлу.\n";
	cout << "Можлива архiвація декiлькох файлiв. Приклад: ar a RAR.rar file1.txt file2.txt\n";
}
void moveHelp()
{
	cout << "Функцiя виконання move\n";
	cout << "Формат вводу команди:\n";
	cout << "move PATH1 PATH2\n,де PATH1 - директорiя файла,\nPATH2 - куди переносити.\n";
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
	cout<<"\nПрограма написана студентом групи 1КI-12(б) Горобчуком Олегом\n";
	cout<<"Перелiк команд:\n";
	cout<<"ar - архiвування файлу\n";
	cout<<"attrib - вивiд i встановлення атрибутiв файлу\n";
	cout<<"hdd - вивiд вiльного(зайнятого) мiсця на вiнчестерi\n";
	cout<<"ls - вмiст початкового каталогу\n";
	cout<<"ukr - БОНУС :)\n";
}

void ukr()
{
	cout << "Слава Украiнi!\n";
	cout << "Героям Слава!\n";
}

void move()
{
	if(command.argcount == 2)
	{
		MoveFile(command.arguments[0],command.arguments[1]);
	}
	else cout<<"Неправильний ввiд команди";
}

void view()
{
	ShellExecute(NULL,"open",command.arguments[0],NULL,NULL,SW_SHOWNORMAL);
}


void date()
{
	SYSTEMTIME st;
	if (command.arguments[0] && strcmp(command.arguments[0],"change")==0)
		//перевiряємо чи аргумент не пустий якщо не пустий то виконуємо простий вивiд на екран
	{
	GetSystemTime(&st);
	cout <<"Поточна дата:\n";
	if (st.wDay<10) cout << 0; 
	cout <<st.wDay <<".";//
	if (st.wMonth <10)cout<<0;
	cout<<st.wMonth <<"."<<st.wYear << endl;
	cout <<"Введiть поточну дату:\n";
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
	if (i!=3){cout <<"Формат дати невiрний\n"; return;}
	int day = atoi(tokenPtr[0]);
	if (day < 0 || day > 31) {cout <<"Формат дати невiрний\n"; return;}
	int month = atoi(tokenPtr[1]);
	if (month < 0 || month >12) {cout <<"Формат дати невiрний\n"; return;}
	int year = atoi(tokenPtr[2]);
	if (year < 0){cout <<"Формат дати невiрний\n"; return;}
	SYSTEMTIME newSystemTime;
	GetSystemTime(&newSystemTime);
	newSystemTime.wDay=day;
	newSystemTime.wMonth=month;
	newSystemTime.wYear=year;
	if(!SetSystemTime(&newSystemTime)) //якщо дата не 
	{
		cout << "помилка встановлення часу, можливо вiдсутнi права адмiнiстратора\n";
		return;
	}
}
	else
	if (command.arguments[0]==NULL )
	{
	GetSystemTime(&st);
	cout <<"Поточна дата:\n";
	if (st.wDay<10) cout << 0; 
	cout <<st.wDay <<".";
	if (st.wMonth <10) cout<<0;
	cout<<st.wMonth <<"."<<st.wYear << endl;
	}
	else
	{
		printf("Невiрнi аргументи.Дивiтся help.\n");
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
		cout<<"Архiвування успiшне!\n";
	}
	else if (strcmp(command.arguments[0],"e") == 0)
	{
		spawnl(P_WAIT,"WinRAR","WinRAR","","e -std",command.arguments[1],NULL);
		cout<<"Розархiвування успiшне!\n";
	}
	else if (strcmp(command.arguments[0],"d") == 0)
	{
		spawnl(P_WAIT,"WinRAR","WinRAR","","d -std",command.arguments[1],NULL);
		cout<<"Архiв видалений!\n";
	}
	else cout<<"Неправильний параметр!";
}

void attrib()
{
	if(command.argcount == 0)
	{
		cout<<"Error: не введенi параметри для функцii.\n";
	}
	else if (command.argcount == 1)
	{
		WIN32_FIND_DATA sstruct;
		HANDLE hFind = FindFirstFile(command.arguments[0],&sstruct);
		if(hFind!=0)
		{
			cout<<"Встановленi атрибути:\n";
   
				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
				cout<<"Прихований\n"; 

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)
				cout<<"Системний\n";

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
				cout<<"Архiвний\n";

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED)
				cout<<"Зжатий\n";

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				cout<<"Папка\n";

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)
				cout<<"Нормальний\n";

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)
				cout<<"Не iндексований\n";
   
				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
				cout<<"Лише для читання\n";

				if(sstruct.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)
				cout<<"Тимчасовий\n";
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
	if (command.argcount == 0) cout<<"Не введено параметр.\n";
	else
	{
		unsigned int mit = GetDriveType(command.arguments[0]);
		GetVolumeInformation(command.arguments[0],NameBuffer, sizeof(NameBuffer), &VSNumber,
			&MCLength,&FileSF,SysNameBuffer,sizeof(SysNameBuffer));
		GetDiskFreeSpaceEx(command.arguments[0], &free, NULL, NULL);

		if (mit == 0 || mit == 1 || mit == 5)
		{
			cout << "Тип диску: ";
			switch(mit)
			{
			case 0:
				cout<<"диск не визначений.\n";
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
		cout << "Мiтка тома: " << NameBuffer << endl;
		cout << "Файлова система: " << SysNameBuffer << endl;
		cout << "Тип диску: ";
		switch(mit)
		{
			case 2:
				cout<<"removable tool.\n";
				break;
			case 3:
				cout<<"жорсткий диск.\n";
				break;
			case 4:
				cout<<"мережевий диск.\n";
				break;
			case 6:
				cout<<"virtual disk.\n";
				break;
		}
		cout << "Free memory " << command.arguments[0] << " " << (double)free.QuadPart/1024/1024/1024<<" Gb\n"; // свободное место в байтах
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
	cout<<"Програма розроблена студентом групи 1КI-12(б) Горобчуком Олегом\n";
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
			cout << "Невiдома команда.\n";
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