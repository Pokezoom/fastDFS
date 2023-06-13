#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "fcgi_stdio.h"

int recv_save_file(char *user, char *filename, char *md5, long *p_size)
{
    int ret = 0;
    char *file_buf = NULL;
    char *begin = NULL;
    char *p, *q, *k;

    char content_text[512] = {0}; //文件头部信息
    char boundary[512] = {0};     //分界线信息

    //==========> 开辟存放文件的 内存 <===========
    file_buf = (char *)malloc(4096);
    if (file_buf == NULL)
    {
        return -1;
    }

    //从标准输入(web服务器)读取内容
    int len = fread(file_buf, 1, 4096, stdin);
    if(len == 0)
    {
        ret = -1;
        free(file_buf);
        return ret;
    }

    //===========> 开始处理前端发送过来的post数据格式 <============
    begin = file_buf;    //内存起点
    p = begin;

    /*
       ------WebKitFormBoundary88asdgewtgewx\r\n
       Content-Disposition: form-data; user="mike"; filename="xxx.jpg"; md5="xxxx"; size=10240\r\n
       Content-Type: application/octet-stream\r\n
       \r\n
       真正的文件内容\r\n
       ------WebKitFormBoundary88asdgewtgewx
       */

    //get boundary 得到分界线, ------WebKitFormBoundary88asdgewtgewx
    p = strstr(begin, "\r\n");
    if (p == NULL)
    {
        ret = -1;
        free(file_buf);
        return ret;
    }

    //拷贝分界线
    strncpy(boundary, begin, p-begin);
    boundary[p-begin] = '\0';   //字符串结束符
    //LOG(UPLOAD_LOG_MODULE, UPLOAD_LOG_PROC,"boundary: [%s]\n", boundary);

    p += 2; //\r\n
    //已经处理了p-begin的长度
    len -= (p-begin);
    //get content text head
    begin = p;
    //Content-Disposition: form-data; user="mike"; filename="xxx.jpg"; md5="xxxx"; size=10240\r\n
    p = strstr(begin, "\r\n");
    if(p == NULL)
    {
        ret = -1;
        free(file_buf);
        return ret;
    }
    strncpy(content_text, begin, p-begin);
    content_text[p-begin] = '\0';

    p += 2;//\r\n
    len -= (p-begin);

    //========================================获取文件上传者
    //Content-Disposition: form-data; user="mike"; filename="xxx.jpg"; md5="xxxx"; size=10240\r\n
    q = begin;
    q = strstr(begin, "user=");
    q += strlen("user=");
    q++;    //跳过第一个"
    k = strchr(q, '"');
    strncpy(user, q, k-q);  //拷贝用户名
    user[k-q] = '\0';

    //========================================获取文件名字
    //"; filename="xxx.jpg"; md5="xxxx"; size=10240\r\n
    begin = k;
    q = begin;
    q = strstr(begin, "filename=");
    q += strlen("filename=");
    q++;    //跳过第一个"
    k = strchr(q, '"');
    strncpy(filename, q, k-q);  //拷贝文件名
    filename[k-q] = '\0';

    //========================================获取文件MD5码
    //"; md5="xxxx"; size=10240\r\n
    begin = k;
    q = begin;
    q = strstr(begin, "md5=");
    q += strlen("md5=");
    q++;    //跳过第一个"
    k = strchr(q, '"');
    strncpy(md5, q, k-q);   //拷贝文件名
    md5[k-q] = '\0';

    //========================================获取文件大小
    //"; size=10240\r\n
    begin = k;
    q = begin;
    q = strstr(begin, "size=");
    q += strlen("size=");
    k = strstr(q, "\r\n");
    char tmp[256] = {0};
    strncpy(tmp, q, k-q);   //内容
    tmp[k-q] = '\0';
    *p_size = strtol(tmp, NULL, 10); //字符串转long

    begin = p;
    p = strstr(begin, "\r\n");
    // 跳过最后一个请求头行和空行
    p += 4; //\r\n\r\n
    // len就是正文的起始位置到数组结束的长度
    len -= (p-begin);

    //下面才是文件的真正内容
    /*
       ------WebKitFormBoundary88asdgewtgewx\r\n
       Content-Disposition: form-data; user="mike"; filename="xxx.jpg"; md5="xxxx"; size=10240\r\n
       Content-Type: application/octet-stream\r\n
       \r\n
       真正的文件内容\r\n
       ------WebKitFormBoundary88asdgewtgewx
    */
    begin = p;
    // 将数组中剩余的数据(文件的内容), 写入到磁盘中
    int fd = open(filename, O_CREAT | O_WRONLY, 0664);
    write(fd, begin, len);
    // 1. 文件已经读完了
    // 2. 文件还没读完
    if(*p_size > len)
    {
        // 读文件 -> 接收post数据
        // fread , read  , 返回值>0== 实际读出的字节数; ==0, 读完了; -1, error
        while( (len = fread(file_buf, 1, 4096, stdin)) > 0 )
        {
            // 读出的数据写文件
            write(fd, file_buf, len);
        }
    }
    // 3. 解写入到文件中的分界线删除
    ftruncate(fd, *p_size);
    close(fd);

    free(file_buf);
    return ret;
}

int main()
{
    while(FCGI_Accept() >= 0)
    {
        // int recv_save_file(char *user, char *filename, char *md5, long *p_size)
        char user[24];
        char fileName[32];
        char md5[64];
        long size;
        recv_save_file(user, fileName, md5, &size);
        // filename对应的文件上传到fastdfs
        // 上传得到的文件ID需要写数据库
        // 给客户端发送响应数据
        printf("Content-type: text/plain\r\n\r\n");
        printf("用户名: %s\n", user);
        printf("文件名: %s, md5: %s, size: %ld\n", fileName, md5, size);
        printf("客户端处理数据完毕, 恭喜...");
    }
}
