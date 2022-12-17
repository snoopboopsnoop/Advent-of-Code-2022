#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

struct Sensor {
    pair<long long, long long> m_location;
    long long m_magnitude;

    Sensor(const pair<long long, long long>& location, long long magnitude) {
        m_location = location;
        m_magnitude = magnitude;
    }
    void print() const {
        cout << "sensor at (" << m_location.first << ", " << m_location.second << "), magnitude of "
            << m_magnitude << endl; 
    }
};

long long getMag(const pair<long long, long long>& sensor, const pair<long long, long long>& beacon) {
    return abs(sensor.first - beacon.first) + abs(sensor.second - beacon.second);
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    const long long kLevel = 6;

    vector<Sensor> sensors;
    string line;
    vector<pair<long long, long long>> covered;
    vector<long long> levelBeacons;

    while(getline(in, line)) {
        istringstream sin(line);
        string trash;
        pair<long long, long long> location;
        pair<long long, long long> beacon;

        // x
        sin >> trash >> trash >> trash;
        location.first = stoi(trash.substr(trash.find("=")+1, trash.find(",")));
        // y
        sin >> trash;
        location.second = stoi(trash.substr(trash.find("=")+1, trash.find(":")));
        // bx
        sin >> trash >> trash >> trash >> trash >> trash;
        beacon.first = stoi(trash.substr(trash.find("=")+1, trash.find(",")));
        // by
        sin >> trash;
        beacon.second = stoi(trash.substr(trash.find("=")+1));
        if(beacon.second == kLevel) {
            if(find(levelBeacons.begin(), levelBeacons.end(), beacon.first) == levelBeacons.end()) {
                levelBeacons.push_back(beacon.first);
            }
        }

        sensors.push_back(Sensor(location, getMag(location, beacon)));
    }

    sort(sensors.begin(), sensors.end(), [](const Sensor& a, const Sensor& b) {
        return a.m_location.first < b.m_location.first;
    });

    for(const Sensor& sensor : sensors) {
        sensor.print();
    }
    cout << endl;

    // Sensor sensor = Sensor(make_pair(8, 7), 9);
    for(const Sensor& sensor : sensors) {
        long long min, max;
        cout << endl;
        cout << "sensor: " << endl;
        sensor.print();

        // sensor is above level
        if(sensor.m_location.second < kLevel) {
            cout << "sensor is above level" << endl;
            // if sensor y position + magnitude is past level line
            if(sensor.m_location.second + sensor.m_magnitude >= kLevel) {
                // spaghetti math
                min = sensor.m_location.first - (sensor.m_magnitude + sensor.m_location.second - kLevel);
                max = sensor.m_location.first + (sensor.m_magnitude + sensor.m_location.second - kLevel);
            }
            else continue;
        }
        // sensor below level
        else if(sensor.m_location.second > kLevel) {
            cout << "sensor is below level" << endl;
            // if sensor y position - magnitude is below level line
            if(sensor.m_location.second - sensor.m_magnitude <= kLevel) {
                // spaghetti math
                min = sensor.m_location.first - (kLevel - (sensor.m_location.second - sensor.m_magnitude));
                max = sensor.m_location.first + (kLevel - (sensor.m_location.second - sensor.m_magnitude));
            }
            else continue;
        }
        // on level
        else if(sensor.m_location.second == kLevel) {
            cout << "sensor is on level" << endl;
            min = sensor.m_location.first - sensor.m_magnitude;
            max = sensor.m_location.first + sensor.m_magnitude;
        }
        else continue;

        cout << "range: " << min << " - " << max << endl; 
        auto found = find_if(covered.begin(), covered.end(), [min, max](const pair<long long, long long>& i) {
            //cout << "checking " << i.first << " - " << i.second << " vs " << min << " - " << max << endl;
            return ((i.first <= max && max <= i.second && min <= i.first) ||
                    (i.second >= min && min >= i.first && max >= i.second));
        });

        if(found != covered.end()) {
            if(found->first <= max && max < found->second && min < found->first) {
                found->first = min;
            }
            if(found->second >= min && min > found->first && max > found->second) {
                found->second = max;
            }
        }
        else {
            //cout << "pushing new pair" << endl;
            covered.push_back(make_pair(min, max));
        }

        // cout << "x values that are covered along y=" << kLevel << endl;
        // for(const pair<long long, long long>& i : covered) {
        //     cout << i.first << " - " << i.second << endl;
        // }
    }

    sort(covered.begin(), covered.end(), [](const pair<long long, long long>& a, const pair<long long, long long>& b) {
        return a.first > b.first;
    });

    cout << "x values that are covered along y=" << kLevel << endl;
    for(const pair<long long, long long>& i : covered) {
        cout << i.first << " - " << i.second << endl;
    }
    cout << endl;

    //covered.erase(covered.begin()+1, covered.end());
    auto beg = covered.begin();
    while(beg != covered.end()) {
        int min = beg->first;
        int max = beg->second;
        cout << "range: " << min << " - " << max << endl; 
        auto found = find_if(covered.begin(), covered.end(), [min, max](const pair<long long, long long>& i) {
            cout << "checking " << i.first << " - " << i.second << " vs " << min << " - " << max << endl;
            if(i.first == min && i.second == max) { cout << "same" << endl; return false; }
            return ((i.first <= max && max <= i.second && min <= i.first) ||
                    (i.second >= min && min >= i.first && max >= i.second) ||
                    (i.first <= min && i.second >= max));
        });

        if(found != covered.end()) {
            cout << "found overlap" << endl;
            if(found->first <= max && max < found->second && min < found->first) {
                found->first = min;
            }
            if(found->second >= min && min > found->first && max > found->second) {
                found->second = max;
            }
            covered.erase(beg);
        }
        else { 
            cout << "no overlap / consumed" << endl;
            beg++;
        }
        cout << "x values that are covered along y=" << kLevel << endl;
        for(const pair<long long, long long>& i : covered) {
            cout << i.first << " - " << i.second << endl;
        }
        cout << endl;
    }
    cout << endl;

    cout << "x values that are covered along y=" << kLevel << endl;
    for(const pair<long long, long long>& i : covered) {
        cout << i.first << " - " << i.second << endl;
    }

    long long subtract = 0;
    for(long long i : levelBeacons) {
        cout << "excluding position " << i << endl;
        auto found = find_if(covered.begin(), covered.end(), [i] (const pair<long long, long long>& range) {
            return (i >= range.first && i <= range.second);
        });
        if(found != covered.end()) subtract++;
    }

    long long result = 0;

    for(const pair<long long, long long>& i : covered) {
        result += i.second - i.first + 1;
    }

    result -= subtract;

    cout << "result: " << result << endl;

    return 0;
}