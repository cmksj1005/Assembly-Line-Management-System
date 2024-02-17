#include "LineManager.h"

using namespace std;

namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		vector<string> startStation{};
		vector<string> endStation{};
		vector<string> roStation{}; // ro = right order
		size_t noSecondStation = -1;

		//assign stations to m_activeLine
		m_activeLine = stations;

		//open the file
		ifstream infile;
		infile.open(file);
		//read each line in the file
		string line;
		while (infile.peek()!=EOF) { //if the next char is EOF, stop looping
			getline(infile, line);
			//if the line has delimiter / if the line have second station
			if (line.find(Utilities::getDelimiter()) != noSecondStation) {
				//push first station of each line to start_station
				startStation.push_back(line.substr(0, line.find(Utilities::getDelimiter())));
				//push second station of each line to start_station
				endStation.push_back(line.substr(line.find(Utilities::getDelimiter()) + 1, (line.find("\n") - 1) - (line.find(Utilities::getDelimiter()))));
			}
			else { //in the line doesn't have second station, set endStation empty.
				startStation.push_back(line.substr(0, line.find('\n')));
				endStation.push_back("");
			}

		}
		infile.close();

		//find the first station and push back to roStation
		copy_if(startStation.begin(), startStation.end(), back_inserter(roStation), [&](const string& startStr) {
			//if 'find' finds nothing, it returns endStation.end()
			return find(endStation.begin(), endStation.end(), startStr) == endStation.end();
			});
		//push back rest of the roStation
		size_t roIndex{};
		for_each(startStation.begin(), startStation.end(), [&](const string& nothing) {
			//find the position
			size_t StationPos{};
			size_t fixedPos{}; // since I don't know how to break for_each, I assigned the value to fixedPos when I found the position
			for_each(startStation.begin(), startStation.end(), [&](const string& startStationStr) {
				if (roStation[roIndex] != startStationStr) {
					StationPos++;
				}
				else {
					fixedPos = StationPos;
				}
				});
			//if endStation is not empty
			if (endStation[fixedPos] != "") {
				roStation.push_back(endStation[fixedPos]);
			}
			//inclease roStation index
			roIndex++;
			});
		//point to the last work station
		Workstation* tempStation{};
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* eachStation) {
			//set the last work station address to 'tempStation'
			if (eachStation->getItemName() == roStation[m_activeLine.size() - 1]) {
				tempStation = eachStation;
			}
			});

		for_each(roStation.rbegin() + 1, roStation.rend(), [&](const string& eachName) {
			for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* eachStation) {
				if (eachStation->getItemName() == eachName) {
					eachStation->setNextStation(tempStation);
					//if eachName is not the first station name
					if (eachName != roStation[0]) {
						tempStation = eachStation;
					}
				}
				});
			});
			//set the first work station
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* eachStation) {
			if (eachStation->getItemName() == roStation[0]) {
				eachStation->setNextStation(tempStation);
				m_firstStation = eachStation;
			}
			});
		//reorder the activeLine like loaded order
		vector<Workstation*> loadedOrder{};
		for_each(startStation.begin(), startStation.end(), [&](const string& str) {
			copy_if(m_activeLine.begin(), m_activeLine.end(), std::back_inserter(loadedOrder), [&](const Workstation* eachStation) {
				return str == eachStation->getItemName();
				});
			});

		m_activeLine = loadedOrder;
	}

	void LineManager::reorderStations() {
		vector<Workstation*> temp{};
		//put first station to temp
		copy_if(m_activeLine.begin(), m_activeLine.end(), std::back_inserter(temp), [&](const Workstation* each) {
			return each->getItemName() == m_firstStation->getItemName();
			});
		//put second station to temp
		copy_if(m_activeLine.begin(), m_activeLine.end(), std::back_inserter(temp), [&](const Workstation* each) {
			return each == m_firstStation->getNextStation();
			});
		//put rest of the stations to temp
		for (size_t i = 1; i < m_activeLine.size() - 1; i++) {
			copy_if(m_activeLine.begin(), m_activeLine.end(), std::back_inserter(temp), [&](const Workstation* each) {
				return each == temp[i]->getNextStation();
				});
		}
		m_activeLine = temp;
	}

	bool LineManager::run(std::ostream& os) {
		size_t orderCount = g_pending.size();
		size_t iCount{};
		bool result = false;

		while (orderCount != (g_completed.size() + g_incomplete.size())) {
			os << "Line Manager Iteration: " << ++iCount << endl;
			//if g_pending doesn't have a value, do not run the codes in the if statement
			if (g_pending.size() > 0) {
				*m_firstStation += std::move(g_pending.front());
				g_pending.pop_front();
			}
			//for each station on the line, executes one fill operation
			for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* eachStation) {
				eachStation->fill(os);
				});
			//for each station on the line, attempts to move an order down the line
			for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* eachStation) {
				eachStation->attemptToMoveOrder();
				});
		}

		if (orderCount == (g_completed.size() + g_incomplete.size())) {
			result = true;
		}

		return result;
	}

	void LineManager::display(std::ostream& os) const {
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* eachStation) {
			eachStation->display(os);
			});
	}
}