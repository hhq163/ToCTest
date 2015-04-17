#include "Config.h"

#include <iostream>
#include <fstream>

CConfig g_oConfig;

static void remove_space(string& str)
{
    string buff(str);
    char space = ' ';
    str.assign(buff.begin() + buff.find_first_not_of(space), buff.begin() + buff.find_last_not_of(space) + 1);
}

CConfig::CConfig()
{
    m_dwID         = 0;
    m_dwHostIp     = 0;
    m_wHostPort    = 0;
    m_wLogLevel    = 0x0040;//debug级别
}

CConfig::~CConfig()
{
}

/**
 * 参数解析
 */
int CConfig::ArgsParse(int argc, char **argv)
{
    char* pPos = NULL;
    char sArg[50];
    if (argc < 2 || argc%2 == 0)
    {
        printf("ArgsParse failed, argc:%d\r\n", argc);
        return -1;
    }

    for (int i = 1; i < argc; i += 2)
    {
        if(NULL == argv[i+1] )
            continue;
        if(strlen(argv[i+1]) > 50)
            continue;
        memset(sArg, 0, 50);
        strcpy(sArg, argv[i+1]);

        if (strcmp("-id", argv[i]) == 0)
        {
            m_dwID = atoi(sArg);
//            printf("ArgsParse, m_dwID:%d\r\n", m_dwID);
        }
        else if (strcmp("-tcp", argv[i]) == 0)
        {
            pPos = strstr(sArg, ":");
            if(NULL == pPos)
            {
                return -2;
            }

            pPos[0] = 0;
            m_dwHostIp = ntohl(inet_addr(sArg));
            m_wHostPort = atoi(pPos+1);
//            printf("ArgsParse, m_wHostPort:%d\r\n", m_wHostPort);
        }
    }

    return 0;
}

bool CConfig::Load()
{

    const char* pFileName;
    pFileName = SERVER_CONFIG_FILE;
    if (NULL == pFileName)
    {
        return false;
    }

    ifstream fin(pFileName);
    if (!fin.is_open())
    {
        return false;
    }

    string strLine;
    string strSection;
    string strName;
    string strValue;
    string::size_type begin = 0;
    string::size_type end = 0;

    while (!fin.eof())
    {
        strLine.clear();
        begin = end = 0;

        getline(fin, strLine, '\n');
        if (strLine.empty() || strLine[0] == '\r' || strLine[0] == '\n' || strLine[0] == '#')
        {
            continue;
        }

        if (strLine[0] == '[')
        {
            end = strLine.find_first_of("]", begin);
            if (string::npos != end)
            {
                strSection = strLine.substr(begin+1, end-1);
            }
            continue;
        }

        if (!Parse(strLine, strName, strValue))
        {
            continue;
        }


        if ("COMMON" == strSection)
        {
            if ("email_address" == strName)
            {
                m_strEmailAddress = strValue;
                m_strEmailAddress = replace_all_distinct(m_strEmailAddress, "/", " ");
//                printf("m_strEmailAddress:%s\r\n", m_strEmailAddress.c_str());
            }
            else if("log_level" == strName){
                m_wLogLevel = atoi(strValue.c_str());
            }
        }
        else if ("WEB_SERVER_INFO" == strSection)
        {
            if ("svr_port" == strName)
            {
                m_wWebSvrPort = atoi(strValue.c_str());
            }
            else if("web_ip" == strName)
            {
                m_dwWebIp = ntohl(inet_addr(strValue.c_str()));
            }
            else if ("web_port" == strName)
            {
                m_wWebPort = atoi(strValue.c_str());
            }
            else if ("http_api_head" == strName)
            {
                m_strHttpApiHead = strValue;
            }
            else if ("http_api_url" == strName)
            {
                m_strHttpApiUrl = strValue;
//                printf("m_strHttpApiUrl:%s\r\n", strValue.c_str());
            }
        }
    }

    fin.close();
    return true;
}


bool CConfig::Parse(string& strLine, string& strName, string& strValue)
{
    string::size_type begin = 0;
    string::size_type end = 0;

    end = strLine.find_first_of("=", begin);
    if (string::npos != end)
    {
        strName = strLine.substr(begin, end);
        remove_space(strName);
        begin = end + 1;
        end = strLine.find_first_of(";", begin);
        if (string::npos != end)
        {
            strValue = strLine.substr(begin, end-begin);
            remove_space(strValue);
            return true;
        }
        cout << "the line can't find the \";\"" << endl;
    }
    else
    {
        cout << "the line can't find the \"=\"" << endl;
    }

    return false;
}
/**
 * 字符串替换
 */
string& CConfig::replace_all_distinct(string& str,const string& old_value,const string& new_value)
{
    for(string::size_type pos(0); pos != string::npos; pos += new_value.length())
    {
        if( (pos=str.find(old_value,pos)) != string::npos )
            str.replace(pos,old_value.length(),new_value);
        else
            break;
    }
    return   str;
}

