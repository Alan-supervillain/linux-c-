/* 对环境的检测后    数据上传服务器的sqlite */
/*经过运行ok*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/usr/local/sqlite/include/sqlite3.h"

typedef	unsigned char	    UINT8;
typedef	unsigned short	UINT16;

int query(sqlite3 *db,char *sql){
	int nrow = 0, ncolumn = 0;
	int i,j;
	char *zErrMsg = 0;
	char **azResult; //二维数组存放结果
	sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );

	printf( "[SQLite]row:%d column=%d \n" , nrow , ncolumn );
	for( i=0 ; i< nrow + 1; i++ ){
		for( j=0 ; j< ncolumn ; j++ ){
			printf( "%s ",azResult[i * ncolumn + j]);
		}
		printf( "\n");
	}
	//释放掉 azResult 的内存空间
	sqlite3_free_table( azResult );
}

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   printf("[SQLite]%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s  ", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


int main(int argc, char* argv[])
{
	sqlite3 *db=NULL;
	int rc;
	char *zErrMsg = 0;
	int i,j;

	printf("[SQLite]===================open=================\n");

	rc = sqlite3_open("/home/alan/test-linux/c/sqlite3/environment.db", &db); //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件
	if(rc)
	{
		//fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		printf("[SQLite]Can't open database: %s\n",sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(-1);
	}
	printf("[SQLite]===================create=================\n");
	//创建一个表,如果该表存在，则不创建，并给出提示信息，存储在 zErrMsg 中
	char *sql = "CREATE TABLE environment(dev_id SMALLINT  NOT NULL,dev_id_name CHAR   NOT NULL, time VARCHAR(12) NOT NULL ,temp_du SMALLINT ,shidu  CHAR ,ps VARCHAR(12));";
	 //\ ; CREATE TABLE BLOBData(ID INTEGER PRIMARY KEY,BData BLOB);

	sqlite3_exec( db , sql , 0 , 0 , &zErrMsg);

	printf("[SQLite]===================insert=================\n");//增
		#define sql sql_char
		char sql[1024] = {0}; 

		sprintf(sql,"INSERT INTO environment VALUES( %d,'test','11-11-11',%d,%d, '备注');",1,36,89);//该sql是插入一行数据
		
		sqlite3_exec(db , sql, 0, 0, &zErrMsg);
		#undef  sql
	printf("[SQLite]===================query=================\n");//查
	
	sql = "SELECT * FROM environment;";

	query(db,sql);
	printf("[SQLite]===================delete=================\n");//删
	
	//删除数据
	//sql = "DELETE FROM environment WHERE Num = 0;" ;
	//sqlite3_exec( db , sql , 0 , 0 , &zErrMsg );

	printf("[SQLite]===================update=================\n");//改

	//sql = "UPDATE environment SET xxxx = 'xxxx' WHERE Num = xxxxxx;" ;
	//sqlite3_exec( db , sql , 0 , 0 , &zErrMsg );

	printf("[SQLite]===================query=================\n");

	sql = "SELECT * FROM environment;";
	const char* data = "Callback";
	rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
	if( rc != SQLITE_OK ){
      printf("[SQLite]SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
	}else{
      printf("[SQLite]Operation done successfully\n");
	}
#if 0
	printf("[SQLite]===================insert blob=================\n");
	sqlite3_stmt* stat;//重复使用 sqlite3_prepare 解析好的 sqlite3_stmt 结构，需要用函数： sqlite3_reset。
	sqlite3_prepare( db, "INSERT INTO BLOBData(ID,BData) VALUES( NULL, ?)", -1, &stat, 0 );
	


	//char* buf = "abc#START* hello#END*#START* hello#END*"; 
	UINT8 buff[41] = {0};
	UINT16 u16Data = 5;
	memcpy(buff,"abc#START*",strlen("abc#START*"));
	buff[10] = (UINT8)(u16Data >> 8);
	buff[11] = (UINT8)u16Data;

	//memcpy(buff + 10,&u16Data,2);
	memcpy(buff + 12,"hello#END*#START*",strlen("hello#END*#START*"));
	buff[29] = (UINT8)(u16Data >> 8);
	buff[30] = (UINT8)u16Data;
	memcpy(buff + 31,"hello#END*",strlen("hello#END*"));
	//printf("[client]buff %s\n",buff);


	// pdata为数据缓冲区，length_of_data_in_bytes为数据大小，以字节为单位
	sqlite3_bind_blob(stat, 1, (const void *)buff, sizeof(buff), NULL);
	
	int result = sqlite3_step(stat);

	printf("[SQLite]SQL: %d %s\n", result,sqlite3_errmsg(db));

	sqlite3_finalize( stat ); //把刚才分配的内容析构掉

	printf("[SQLite]===================query blob=================\n");

	sqlite3_stmt * stat_q;
	sqlite3_prepare( db,"select * from BLOBData", -1, &stat_q, 0 );
	int result1 = sqlite3_step( stat_q );
	printf("[SQLite]SQL: %d %s\n", result1,sqlite3_errmsg(db));

	int id = sqlite3_column_int( stat_q, 0 ); //第2个参数表示获取第几个字段内容，从0开始计算，因为我的表的ID字段是第一个字段，因此这里我填0
	UINT8* pContent = (UINT8*)sqlite3_column_blob( stat_q, 1 );
	int len = sqlite3_column_bytes( stat_q, 1 );
	printf("[SQLite]SQL len: %d\n", len);
	for ( i = 0; i < 41; i++)
	{
		printf("[%02x]",pContent[i]);
	}
	printf("\n");

	sqlite3_finalize( stat_q ); //把刚才分配的内容析构掉
	printf("[SQLite]===================close=================\n");
#endif
	sqlite3_close(db); //关闭数据库
	return 0;
}

