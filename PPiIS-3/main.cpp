#include <iostream>;
#include <cstring>;
#include <vector>;
#include <queue>

using namespace std;

struct passenger
{
	int _number;

	passenger() : 
		_number(0)
	{}

	passenger(int number) :
		_number(number)
	{}
};

struct cargo
{
	int _number;

	cargo() :
		_number(0)
	{}

	cargo(const int number) :
		_number(number)
	{}
};



class carriage
{
public:

	virtual void cloading(const int& value) = 0;
	virtual int cunloading() = 0;

protected:

};

class PassengerCarriage : public carriage
{
public:

	PassengerCarriage()
	{
		_passengers._number = 0;
	}

	PassengerCarriage(const int number)
	{
		_passengers._number = number;
	}

	void cloading(const int& value) override
	{
		_passengers._number = value;
	}

	int cunloading() override
	{
		int t;
		t = _passengers._number;
		_passengers._number = 0;
		return t;
	}

protected:
	passenger _passengers;
};

class CargoCarriage : public carriage
{
public:

	CargoCarriage()
	{
		_cargo._number = 0;
	}

	CargoCarriage(const int number)
	{
		_cargo._number = number;
	}

	void cloading(const int& value) override
	{
		_cargo._number = value;
	}

	int cunloading() override
	{
		int t;
		t = _cargo._number;
		_cargo._number = 0;
		return t;
	}

protected:
	cargo _cargo;
};



class train
{
public:
	train() :
		_name("A"),
		_type("broken"),
		_station("Minsk")
	{	}
	train(const string& name, const string& type, const string& station) :
		_name(name),
		_type(type),
		_station(station)
	{	}
	virtual void tloading(const int& value) = 0;
	virtual const int tunloading() = 0;
	virtual const string get_name()
	{
		return _name;
	}
	virtual const string get_type()
	{
		return _type;
	}
	virtual const string get_station()
	{
		return _station;
	}
	virtual void set_station(const string& name)
	{
		_station = name;
	}
	friend class map;
protected:
	string _type;
	string _name;
	string _station;
};

class PasTrain : public train
{
public:
	PasTrain() : train()
	{
		_carriages = new PassengerCarriage[20];
	}

	PasTrain(const string& _name, const string& _type, const string& station) : train(_name, _type, _station)
	{
		_carriages = new PassengerCarriage[20];
	}

	void tloading(const int& value) override
	{
		int t = value;
		for (int i = 0; i < 20; i++)
		{			
			if (t >= 0 || t < 50)
				_carriages[i].cloading(t);
			else if (t >= 50)
			{
				t -= 50;
				_carriages[i].cloading(50);
			}
		}
	}

	int const tunloading() override
	{
		int t = 0;
		for (int i = 0; i < 20; i++)
		{
			t = _carriages[i].cunloading();
		}
		return t;
	}

protected:
	PassengerCarriage* _carriages;
};

class CargoTrain : public train
{
public:
	CargoTrain() : train()
	{
		_carriages = new CargoCarriage[20];
	}

	CargoTrain(const string& _name, const string& _type, const string& _station) : train(_name, _type, _station)
	{
		_carriages = new CargoCarriage[20];
	}

	void tloading(const int& value) override
	{
		int t = value;
		for (int i = 0; i < 20; i++)
		{
			if (t >= 0 || t < 50)
				_carriages[i].cloading(t);
			else if (t >= 50)
			{
				t -= 50;
				_carriages[i].cloading(50);
			}
		}
	}

	int const tunloading() override
	{
		int t = 0;
		for (int i = 0; i < 20; i++)
		{
			t = _carriages[i].cunloading();
		}
		return t;
	}

protected:
	CargoCarriage* _carriages;
};
/*
class TrainFactory
{
public:
	virtual train create_train(const string& name, const string& type, const string& station) = 0;
private:
};

class PasTrainFactory : public TrainFactory
{
public:
	PasTrain create_train(const string& name, const string& type, const string& station)
	{
		PasTrain A(name, "pas", station);
		return A;
	}
private:
};

class CargoTrainFactory : public TrainFactory
{

};
*/



class station
{
public:
	station()
	{
		_passengers = 3000;
		_cargo = 3000;
		_name = "Minsk";
		_number++;
	}

	station(const int cargo, const int passengers, const string name, const int number) :
		_cargo(cargo),
		_passengers(passengers),
		_name(name),
		_number(number)
	{	}

	void loading(train& train, const int& cargo, const int& passengers)
	{
		if (cargo == 0 && passengers > 0)
		{
			if (passengers >= 400 && passengers <= _passengers)
			{
				train.tloading(400);
				_passengers -= 400;
			}
			else if (passengers >= _passengers && passengers <= 400)
			{
				train.tloading(_passengers);
				_passengers = 0;
			}
			else if (passengers <= _passengers && passengers <= 400)
			{
				train.tloading(passengers);
				_passengers -= passengers;
			}
		}
		else if (cargo > 0 && passengers == 0)
		{
			if (cargo >= 400 && cargo <= _cargo)
			{
				train.tloading(400);
				_cargo -= 400;
			}
			else if (cargo >= _cargo && cargo <= 400)
			{
				train.tloading(_cargo);
				_cargo = 0;
			}
			else if (cargo <= _cargo && cargo <= 400)
			{
				train.tloading(cargo);
				_cargo -= cargo;
			}
		}
		else if (cargo > 0 && passengers > 0)
			cout << "\nChoose only one!";
		/*
		else if (cargo > 0 && passengers > 0)
		{
			if (cargo >= 200 && cargo <= _cargo && passengers >= 200 && passengers <= _passengers)
			{
				train.tloading(200);
				_cargo -= 200;
			}
			else if (cargo >= _cargo && cargo <= 200 && passengers <= 200 && passengers >= _passengers)
			{
				train.tloading(_cargo);
				_cargo = 0;
			}
			else if (cargo <= _cargo && cargo <= 200 && passengers <= 200 && passengers <= _passengers)
			{
				train.tloading(cargo);
				_cargo -= cargo;
			}
			else if (cargo <= _cargo && cargo <= 200 && passengers <= 200 && passengers >= _passengers)
			{
				train.tloading(cargo);
				_cargo -= cargo;
			}
		}
		*/
	}

	int unloading(train& train)
	{
		return train.tunloading();
	}

	string get_name()
	{
		return _name;
	}

	int get_number() 
	{
		return _number;
	}

	friend class map;

protected:
	int _number;
	string _name;
	int _passengers;
	int _cargo;
};

class map
{
public:
	map() :
		_vertexes(0),
		_edges(0),
		_graph{0},
		_stations{},
		_CargoTrains{},
		_PasTrains{}
	{	}
	map(const int& vertexes, const int& edges) :
		_vertexes(vertexes),
		_edges(edges),
		_graph {0},
		_stations{},
		_CargoTrains{},
		_PasTrains{}
	{	}

	int find_station_number(const string& name)
	{
		for (int i = 0; i < _stations.size(); i++)
		{
			if (name == _stations[i]->get_name())
				return _stations[i]->get_number();
			break;
		}
	}

	string find_station_name(const int& number)
	{
		for (int i = 0; i < _stations.size(); i++)
		{
			if (number == _stations[i]->get_number())
				return _stations[i]->get_name();
			break;
		}
	}

	void create_way()
	{
		string from, to;
		int weight;
		int u = 0, v = 0;
		cout << "\nWrite dispatch station: ";
		cin >> from;
		for (int k = 0; k < _stations.size(); k++)
			if (from == _stations[k]->_name)
				u = _stations[k]->_number;
		cout << "\nWrite arrival station: ";
		cin >> to; 
		for (int k = 0; k < _stations.size(); k++)
			if (to == _stations[k]->_name)
				v = _stations[k]->_number;
		cout << "\nWrite way length: ";
		cin >> weight;
		system("cls");
		_graph[u][v] = _graph[v][u] = weight;
	}

	void create_stations(const int numbers)
	{
		_edges = numbers;
		for (int i = 0; i < numbers; i++)
		{
			station* cur = new station;

			cout << "\nWrite name of the " << i + 1 <<" station: ";
			cin >> cur->_name;

			cout << "\nWrite quantity of cargo: ";
			cin >> cur->_cargo;

			cout << "\nWrite quantity of passengers: ";
			cin >> cur->_passengers;

			cur->_number = i;

			_stations.push_back(cur);

			system("cls");
		}
	}

	void get_short_map_of_ways()
	{
		int c;
		string cur;
		for (int i = 0; i < _edges; i++)
		{
			c = 0;
			for (int k = 0; k < _edges; k++)
			{
				if (_graph[i][k])
				{
					c++;
				}
			}

			cur = find_station_name(i);

			cout << c << " railways are came from " << cur << endl;
		}
	}

	station find_station(const string& name)
	{
		for (int i = 0; i < _stations.size(); i++)
		{
			if (name == _stations[i]->get_name())
			{
				return *_stations[i];
				break;
			}
		}
	}

	void find_a_way(const string& train, const string& seccond)
	{
		string first;

		for (int i = 0; i < _CargoTrains.size(); i++)
		{
			if (train == _CargoTrains[i].get_name())
				first = _CargoTrains[i].get_station();
		}

		for (int i = 0; i < _CargoTrains.size(); i++)
		{
			if (train == _CargoTrains[i].get_name())
				_CargoTrains[i].set_station(seccond);
		}

		for (int i = 0; i < _CargoTrains.size(); i++)
		{
			if (train == _PasTrains[i].get_name())
				first = _PasTrains[i].get_station();
		}

		for (int i = 0; i < _PasTrains.size(); i++)
		{
			if (train == _PasTrains[i].get_name())
				_PasTrains[i].set_station(seccond);
		}

		int from = find_station_number(first);
		int to = find_station_number(seccond);
		string to2;
		vector<int> start(_edges, -1);
		vector<int> used(_edges, 0);
		vector<int> dist(_edges);

		bool find = false;

		queue<int> q;
		q.push(from);

		dist[from] = 0;
		used[from] = 1;;

		while (!q.empty())
		{
			int t = q.front();
			q.pop();

			for (int i = 0; i < _edges; ++i)
			{
				if (_graph[t][i] && !used[i])
				{
					dist[i] = dist[t] + _graph[t][i];
					start[i] = t;
					q.push(i);
					used[i] = true;
				}
			}
		}

		if (used[to])
		{
			vector<string> path;
			while (start[to] != -1)
			{
				path.push_back(to2 = find_station_name(to));
				to = start[to];
			}

			path.push_back(to2 = find_station_name(to));

			cout << "Length of the way: " << dist[to] << endl;
			cout << "Way:\n";
			for (int i = path.size() - 1; i >= 0; i--)
				cout << path[i] << " - ";
			cout << '\n';
		}
		else
			cout << "\nNo ways from current station to selected station!\n";
	}

	void create_train(const string& type, const string& name, const string& station)
	{
		if (type == "pas")
		{
			PasTrain A(name, "pas", station);
			_PasTrains.push_back(A);
		}
		else if (type == "cargo")
		{
			CargoTrain A(name, "cargo", station);
			_CargoTrains.push_back(A);
		}
	}

	void get_trains(const string& station)
	{
		cout << "Cargo trains:" << endl;
		for (int i = 0; i < _CargoTrains.size(); i++)
		{
			if (station == _CargoTrains[i].get_station())
				cout << _CargoTrains[i].get_name() << endl;
		}
		cout << "Passenger trains:" << endl;
		for (int i = 0; i < _PasTrains.size(); i++)
		{
			if (station == _PasTrains[i].get_station())
				cout << _PasTrains[i].get_name() << endl;
		}
	}
private:
	int _vertexes;
	int _edges;
	int _graph[30][30]{};
	vector<station*> _stations;
	vector<CargoTrain> _CargoTrains;
	vector<PasTrain> _PasTrains;
};

void PseudoUI(map World)
{
	int c, numb = 0;
	bool q = true;
	while (q == true)
	{
		cout << "\nSelect operation:" << endl
			<< "   1. Create stations (out of 30)\n   2. Create ways\n   3. Create train\n   4. Load train\n   5. Unload train\n   6. Move train\n   7. Exit\n\nYour choise: ";
		cin >> c;
		system("cls");

		switch (c)
		{
		case 1:
			cout << "\nWrite numbers of stations: ";
			cin >> numb;
			system("cls");
			World.create_stations(numb);
			break;
		case 2:
			World.create_way();
			break;
		case 3:
			string name, type, station;
			World.create_train()
		case 4:
			q = false;
			break;
		}
	}
	
}

int main()
{
	map World;
	PseudoUI(World);
	return 0;
}