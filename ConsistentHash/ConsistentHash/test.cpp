#include<set>
#include<string>
#include<iostream>
#include<list>
#include<vector>
using namespace std;
using uint = unsigned int;

class Virtual;

// 物理节点
class Physical
{
private:
	string ip_;					//物理IP
	list<Virtual> virtualHost;	//虚拟节点
public:
	Physical(string ip, int numOfVirtual)
		:ip_(ip)
	{
		for (int i = 0; i < numOfVirtual; i++)
		{
			virtualHost.emplace_back(
				ip + '#' + to_string(i),
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

// 虚拟节点
class Virtual
{
private:
	string ip_;					//虚拟IP
	Physical* physicalHost_;	//物理节点
	uint md5;
public:
	Virtual(string ip, Physical* p)
		: ip_(ip)
		, physicalHost_(p)
	{
		md5 = ::getMD5(ip.c_str());
	}
	string getVirtualIP() const
	{
		return ip_;
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
		return md5 == host.md5;
	}
};

// 一致性哈希
class ConsistentHash
{
private:
	set<Virtual> hashCircle;	//一次性哈希环
public:
	//添加物理节点的虚拟节点
	void addHost(const Physical& host)
	{
		auto list = host.getVirtualHost();
		for (const auto& it : list)
		{
			hashCircle.insert(it);
		}
	}

	//删除物理节点的虚拟节点
	void deleteHost(const Physical& host)
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
	//返回负载的物理主机ip信息
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
	// 新增：打印所有虚拟节点的 hash 分布
	void printVirtualNodes() const {
		cout << "虚拟节点分布 (hash, 虚拟IP, 物理IP):" << endl;
		for (const auto& vhost : hashCircle) {
			cout << vhost.getMD5() << ", " << vhost.getVirtualIP() << ", " << vhost.getPhysicalHost()->getIP() << endl;
		}
	}
};


int main()
{
	// 创建物理节点
	Physical host1("192.168.1.1", 150);
	Physical host2("192.168.1.2", 150);
	Physical host3("192.168.1.3", 150);

	// 创建一致性哈希对象
	ConsistentHash ch;
	ch.addHost(host1);
	ch.addHost(host2);
	ch.addHost(host3);

	// 打印虚拟节点分布
	ch.printVirtualNodes();

	// 测试不同client ip的分布
	vector<string> clientIps = {
		"10.0.0.1",
		"10.0.0.2",
		"10.0.0.3",
		"10.0.0.4",
		"10.0.0.5"
	};

	cout << "初始分布：" << endl;
	for (const auto& ip : clientIps) {
		cout << "Client " << ip << " -> Host " << ch.getHost(ip) << endl;
	}

	// 删除一个物理节点
	ch.deleteHost(host1);
	cout << "\n删除192.168.1.1后分布：" << endl;
	for (const auto& ip : clientIps) {
		cout << "Client " << ip << " -> Host " << ch.getHost(ip) << endl;
	}
	return 0;
}