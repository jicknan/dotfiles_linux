#include "stdio.h"
#include "libfetion/libfetion.h"

void Printf_AllGroup_Info();
void Printf_AllAccount_Info();

int main()
{
	//init the libfetion frist
	if(!fx_init()) {
		fprintf(stderr, "init the app fail \n");
		exit(0);
	}

	//login the fetion
	if(! fs_login("your fetion id", "your fetion password")) {
		fprintf(stderr, "login fail the error code is %d \n", fx_get_lasterror());
		exit(0);
	}


	//here will will show how to get the fetion's group information..
	Printf_AllGroup_Info();


	//here will will show how to get the fetion's group information..
	Printf_AllAccount_Info();
	
	//if you want to send a shormessage to somebody, you can call fs_send_sms..
	//fs_send_sms(uid, msg);

	//login out ....
	fx_loginout();

	//destroy the libfetion
	fx_terminate();
}


void Printf_AllGroup_Info()
{
	Fetion_Group *group = NULL;
	DList *tmp = fx_get_group();
	while(tmp)
	{
		group = (Fetion_Group *) tmp->data;

		if(group) { 
			fprintf(stderr, "the group id is %d, group name is %s \n",
					group->id, group->name);
		}

		tmp = d_list_next(tmp);
	}

}

char* get_show_name(Fetion_Account *account)
{
	char * res;
	if(!account)
		return "";
	if(account->local_name && strcmp(account->local_name, "") != 0)
		return  account->local_name;
	else 	
		if(account->personal) {
			if(account->personal->nickname && strcmp(account->personal->nickname, "") != 0)
				return account->personal->nickname;
			else
				if(account->personal->name && strcmp(account->personal->name, "") != 0)
					return account->personal->name;
		}
		else 
		{
			if(fx_is_pc_user_by_id(account->id)) {
				asprintf(&res ,"%ld", account->id);
				return res;
			} else {
				asprintf(&res ,"13%ld", account->id- 1000000000);
				return res;
			}
		}
	return " ";
}	


void Printf_AllAccount_Info()
{
	Fetion_Account *account = NULL;
	DList *tmp_account = fx_get_account();
	while(tmp_account) 
	{
		 account = (Fetion_Account *)tmp_account->data;  

		 if(account)
		 {
			 int	group_no = fx_get_account_group_id(account);
			 char *showname = get_show_name(account);

			 fprintf(stderr, "the account id is %d, is belong to group %d, it showname is %s \n", account->id, group_no, showname)
		 
		 }

		
		tmp_account = d_list_next(tmp_account);
	}
}

