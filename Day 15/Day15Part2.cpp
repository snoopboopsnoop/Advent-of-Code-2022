#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother
const int kLimit = 4000000;

struct Sensor {
    pair<long, long> m_location;
    long m_magnitude;

    Sensor(const pair<long, long>& location, long magnitude) {
        m_location = location;
        m_magnitude = magnitude;
    }
    void print() const {
        cout << "sensor at (" << m_location.first << ", " << m_location.second << "), magnitude of "
            << m_magnitude << endl; 
    }
};

long getMag(const pair<long, long>& sensor, const pair<long, long>& beacon) {
    return abs(sensor.first - beacon.first) + abs(sensor.second - beacon.second);
}

int searchLevel(int level, const vector<Sensor>& sensors) {
    vector<pair<long, long>> covered;

    for(const Sensor& sensor : sensors) {
        if(covered.size() != 0) {
            if(covered[0].first == 0 && covered[0].second == kLimit) return -1;
        }
        long min, max;
        //cout << endl;
        // cout << "sensor: " << endl;
        // sensor.print();

        // sensor is above level
        if(sensor.m_location.second < level) {
            //cout << "sensor is above level" << endl;
            // if sensor y position + magnitude is past level line
            if(sensor.m_location.second + sensor.m_magnitude >= level) {
                // spaghetti math
                min = sensor.m_location.first - (sensor.m_magnitude + sensor.m_location.second - level);
                max = sensor.m_location.first + (sensor.m_magnitude + sensor.m_location.second - level);
            }
            else continue;
        }
        // sensor below level
        else if(sensor.m_location.second > level) {
            // cout << "sensor is below level" << endl;
            // if sensor y position - magnitude is below level line
            if(sensor.m_location.second - sensor.m_magnitude <= level) {
                // spaghetti math
                min = sensor.m_location.first - (level - (sensor.m_location.second - sensor.m_magnitude));
                max = sensor.m_location.first + (level - (sensor.m_location.second - sensor.m_magnitude));
            }
            else continue;
        }
        // on level
        else if(sensor.m_location.second == level) {
            // cout << "sensor is on level" << endl;
            min = sensor.m_location.first - sensor.m_magnitude;
            max = sensor.m_location.first + sensor.m_magnitude;
        }
        else continue;

        if(max > kLimit) max = kLimit;
        if(min < 0) min = 0;

        // cout << "range: " << min << " - " << max << endl; 
        auto found = find_if(covered.begin(), covered.end(), [min, max](const pair<long, long>& i) {
            // cout << "checking " << i.first << " - " << i.second << " vs " << min << " - " << max << endl;
            return ((i.first <= max && max <= i.second && min <= i.first) ||
                    (i.second >= min && min >= i.first && max >= i.second));
        });

        if(found != covered.end()) {
            if(found->first <= max && max <= found->second && min <= found->first) {
                found->first = min;
            }
            if(found->second >= min && min >= found->first && max >= found->second) {
                found->second = max;
            }
        }
        else {
            //cout << "pushing new pair" << endl;
            covered.push_back(make_pair(min, max));
        }

        // cout << "x values that are covered along y=" << level << endl;
        // for(const pair<long, long>& i : covered) {
        //     cout << i.first << " - " << i.second << endl;
        // }
    }

    sort(covered.begin(), covered.end(), [](const pair<long, long>& a, const pair<long, long>& b) {
        return a.first > b.first;
    });

    auto beg = covered.begin();
    while(beg != covered.end()) {
        int min = beg->first;
        int max = beg->second;
        //cout << "range: " << min << " - " << max << endl; 
        auto found = find_if(covered.begin(), covered.end(), [min, max](const pair<long, long>& i) {
            //cout << "checking " << i.first << " - " << i.second << " vs " << min << " - " << max << endl;
            if(i.first == min && i.second == max) { 
                // cout << "same" << endl;
                return false; }
            return ((i.first <= max && max <= i.second && min <= i.first) ||
                    (i.second >= min && min >= i.first && max >= i.second) ||
                    (i.first <= min && i.second >= max));
        });

        if(found != covered.end()) {
            //cout << "found overlap" << endl;
            if(found->first <= max && max < found->second && min < found->first) {
                found->first = min;
            }
            if(found->second >= min && min > found->first && max > found->second) {
                found->second = max;
            }
            covered.erase(beg);
        }
        else { 
            //cout << "no overlap / consumed" << endl;
            beg++;
        }
        // cout << "x values that are covered along y=" << level << endl;
        // for(const pair<long, long>& i : covered) {
        //     cout << i.first << " - " << i.second << endl;
        // }
        // cout << endl;
    }
    //cout << endl;

    // cout << "x values that are covered along y=" << level << endl;
    // for(const pair<long, long>& i : covered) {
    //     cout << i.first << " - " << i.second << endl;
    // }

    if(covered[0].first == 0 && covered[0].second == kLimit) return -1;

    for(int i = 0; i < kLimit; ++i) {
        if(find_if(covered.begin(), covered.end(), [i](const pair<int, int>& range) {
            return range.first <= i && range.second >= i;
        }) == covered.end()) {
            return i;
        }
    }
    return -1;
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    vector<Sensor> sensors;
    string line;
    const long kTuningFreq = 4000000;

    while(getline(in, line)) {
        istringstream sin(line);
        string trash;
        pair<long, long> location;
        pair<long, long> beacon;

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

        sensors.push_back(Sensor(location, getMag(location, beacon)));
    }

    sort(sensors.begin(), sensors.end(), [](const Sensor& a, const Sensor& b) {
        return a.m_location.first < b.m_location.first;
    });

    for(const Sensor& sensor : sensors) {
        sensor.print();
    }
    cout << endl;

    long result = 0;
    // Sensor sensor = Sensor(make_pair(8, 7), 9);

    //covered.erase(covered.begin()+1, covered.end());
    for(int i = 0; i < kLimit; i++) {
        //cout << "checking y=" << i << endl;
        int temp = searchLevel(i, sensors);
        //cout << "at y = " << i << " there is a possible beacon at x = " << temp << endl;
        if(temp != -1) {
            result = temp * kTuningFreq + i;
            break;
        }
    }

    cout << "result: " << result << endl;

    return 0;
}