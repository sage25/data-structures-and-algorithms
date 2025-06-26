#include<set>
#include<string>
#include<iostream>
#include<list>
#include<vector>
using namespace std;
using uint = unsigned int;

uint getMD5(const string& str)
{
    uint hash = 0;
    for (char c : str)
    {
        hash = (hash * 131) + static_cast<unsigned char>(c); // 131Ϊ���õĹ�ϣ����
    }
    return hash;
}

uint getMD5(const char* str)
{
    return getMD5(string(str));
}

class Virtual;

// ����ڵ�
class Physical
{
private:
	string ip_;					//����IP
	list<Virtual> virtualHost;	//����ڵ�
public:
	Physical(string ip, int numOfVirtual)
		:ip_(ip)
	{
		for (int i = 0; i < numOfVirtual; i++)
		{
			ip_ = ip + '#' + to_string(i);
			virtualHost.emplace_back(
				ip_,
				this
			);
		}
	}
	string getIP() const
	{
		return ip_;
	}
	const list<Virtual>& getVirtualHost() const
	{
		return virtualHost;
	}

};

// ����ڵ�
class Virtual
{
private:
	string ip_;					//����IP
	Physical* physicalHost_;	//����ڵ�
	uint md5;
public:
	Virtual(string ip, Physical* p)
		: ip_(ip)
		, physicalHost_(p)
	{
		md5 = ::getMD5(ip.c_str());
	}
	const Physical* getPhysicalHost() const 
	{
		return physicalHost_;
	}
	uint getMD5() const
	{
		return md5;
	}
	bool operator<(const Virtual& host) const
	{
		return md5 < host.md5;
	}
	bool operator==(const Virtual&  host) const
	{
		return ip_ == host.ip_;
	}
};

// һ���Թ�ϣ
class ConsistentHash
{
private:
	set<Virtual> hashCircle;	//һ���Թ�ϣ��
public:
	//�������ڵ������ڵ�
	void addHost(Physical host)
	{
		auto list = host.getVirtualHost();
		for (auto it : list)
		{
			hashCircle.insert(it);
		}
	}

	//ɾ������ڵ������ڵ�
	void deleteHost(Physical host)
	{
		auto list = host.getVirtualHost();
		for (auto vhost : list)
		{
			auto it = hashCircle.find(vhost);
			if (it != hashCircle.end())
			{
				hashCircle.erase(it);
			}

		}
	}
	//���ظ��ص���������ip��Ϣ
	string getHost(string clientip) const
	{
		uint md5 = ::getMD5(clientip);
		for (auto vhost : hashCircle)
		{
			if (vhost.getMD5() > md5)
			{
				return vhost.getPhysicalHost()->getIP();
			}
		}
		return hashCircle.begin()->getPhysicalHost()->getIP();
	}
};


int main()
{
	// ��������ڵ�
	Physical host1("192.168.1.1", 3);
	Physical host2("192.168.1.2", 3);
	Physical host3("192.168.1.3", 3);

	// ����һ���Թ�ϣ����
	ConsistentHash ch;
	ch.addHost(host1);
	ch.addHost(host2);
	ch.addHost(host3);

	// ���Բ�ͬclient ip�ķֲ�
	vector<string> clientIps = {
		"10.0.0.1",
		"10.0.0.2",
		"10.0.0.3",
		"10.0.0.4",
		"10.0.0.5"
	};

	cout << "��ʼ�ֲ���" << endl;
	for (const auto& ip : clientIps) {
		cout << "Client " << ip << " -> Host " << ch.getHost(ip) << endl;
	}

	// ɾ��һ������ڵ�
	ch.deleteHost(host2);
	cout << "\nɾ��192.168.1.2��ֲ���" << endl;
	for (const auto& ip : clientIps) {
		cout << "Client " << ip << " -> Host " << ch.getHost(ip) << endl;
	}
	return 0;
}