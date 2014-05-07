
int string_id(char s[]);


main()
{
	char a;
	int j;
	while(1)
	{
		int i;
		char command[500];
		char name[100];
		char hold[13312];
		
		interrupt(0x21,0,"CARACOL>",0,0);
		for(i = 0; i<500; i++)
		{
			command[i] = 0;
		}
		interrupt(0x21,1,command,0,0);		/*store contents of keyboard in command*/
		
		a = interrupt(0x16,0,0,0,0);

		if(a == 0xd && command[0] == 't')
		{
			
			interrupt(0x21,0,"Filename: ",0,0);
			interrupt(0x21,1,name,0,0);
			interrupt(0x21,3,name,hold,0);
			interrupt(0x21,0,hold,0,0);

		}
		else if(a == 0xd && command[0] == 'e')
		{
			
			interrupt(0x21,0,"Filename: ",0,0);
			interrupt(0x21,1,name,0,0);
			interrupt(0x21,4,name,0x2000,0);

		}
		else if(a == 0xd && command[0] == 'd' && command[1] == 'e')
		{
			interrupt(0x21,0,"Filename: ",0,0);
			interrupt(0x21,1,name,0,0);
			interrupt(0x21,7,name,0,0);
			interrupt(0x21,0,"File Deleted!",0,0);
		}
		else if(a == 0xd && command[0] == 'c' && command[1] == 'o')
		{
			char name2[100];
			interrupt(0x21,0,"Filename: ",0,0);
			interrupt(0x21,1,name,0,0);
			interrupt(0x21,3,name,hold,0);
			interrupt(0x21,0,"Copy Name: ",0,0);
			interrupt(0x21,1,name2,0,0);
			interrupt(0x21,8,name2,hold,1);
			interrupt(0x21,0,"File copied!");
		}
		//else if(a == 0xd && command[0] == 'd' && command[1] == 'i')
		//{
		//	char dir[512];
		//	interrupt(0x21,2,dir,2,0); //load contents of directory to dir array



		//	interrupt(0x21,0,"Files: ",0,0);
		//	interrupt(0x21,0,temp,0,0);
		//}
		else if(a == 0xd && command[0] == 'c' && command[1] == 'r')
		{
			char name[512];
			interrupt(0x21,0,"Enter text: ",0,0);
			interrupt(0x21,1,hold,0,0);
			interrupt(0x21,0,"Name the new file: ",0,0);
			interrupt(0x21,1,name,0,0);
			interrupt(0x21,8,name,hold,1);
			interrupt(0x21,0,"Great!",0,0);
		}
		else
		{
			interrupt(0x21, 0, "Bad Command!", 0, 0);
		}
	}
}
