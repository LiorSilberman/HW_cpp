#include <sstream>
#include <cmath>
#include "WebListener.h"

WebListener::WebListener(int dim, int max)
: size(0), dimension(dim), max_size(max)
{
    timestamps = new char*[max_size];
    records = new unsigned short*[max_size];
    for (int i = 0; i < max_size; i++)
    {
        timestamps[i] = nullptr;
        records[i]    = nullptr;
    }
}

WebListener::~WebListener()
{
    for (int i = 0; i < max_size; i++)
    {
        if (timestamps[i] != nullptr)
            delete timestamps[i];
        if (records[i] != nullptr)
            delete records[i];
    }
}

int WebListener::get_size() const
{
    return size;
}

int WebListener::get_dimension() const
{
    return dimension;
}

void WebListener::print_histogram(const int histogram[]) const
{
    for (int i = 0; i < get_dimension(); i++)
    {
        std::cout << i + 1 << "\t";
        for (int j = 0; j < histogram[i]; j++)
        {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}

bool WebListener::check_timestamp(const std::string& timestamp)
{
    // check legal timestamp
    if (timestamp.length() > 16)
        return false;

    // check if timestamp in memory
    for (int i = 0; i < size; i++)
        if (timestamp == timestamps[i])
            return true;

    return false;
}

bool WebListener::check_index(int index) const
{
    if (index > dimension)
        return false;

    return true;
}

float WebListener::calculate(int index)
{
    // sum each row
    float sum_matrix = 0;
    float sum_col = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            sum_matrix += (float)records[i][j];
            if (j == index - 1)
                sum_col += (float)records[i][j];
        }
    }

    if (sum_matrix == 0)
    {
        return std::nanf("");
    }
    return sum_col / sum_matrix;
}

bool WebListener::set_record(const std::string& timestamp, std::string record) {
    // max container size reached?
    if (size == max_size - 1)
        return false;

    // check legal timestamp
    if (timestamp.length() > 16)
        return false;


    // convert record to unsigned shorts
    unsigned short web_record[dimension];
    std::string temp;
    int record_runner = 0;
    for(std::string::size_type i = 0; i < record.size(); ++i)
    {
        if (record[i] != ',')
        {
            temp += record[i];

            // not end of string?
            if (i < record.size() - 1)
                continue;
        }
        web_record[record_runner++] = std::stoi(temp);

        // clean temp string
        temp = std::string("");
    }

    // check legal record
    if (record_runner != dimension)
        return false;

    // decide on record location, if record exists in container override old record
    int pose_index = size;
    for (int i = 0; i < size; i++)
        if (timestamp == timestamps[i]) {
            pose_index = i;
            delete timestamps[i];
            delete records[i];
        }

    // insert new record to containers
    timestamps[pose_index] = new char[timestamp.size()];
    timestamp.copy(timestamps[pose_index], timestamp.size());

    records[pose_index] = new unsigned short[dimension];
    for (int i = 0; i < dimension; i++)
        records[pose_index][i] = web_record[i];

    // increase containers size
    if (pose_index == size)
        size++;

    return true;
}

std::string WebListener::get_record(const std::string& timestamp)
{
    // search for timestamp in container
    int pose_index = 0;
    for (int i = 0; i < size; i++)
        if (timestamp == timestamps[i])
            pose_index = i;

    // go to same index in record container and return as string
    std::string record_array;
    int count = 0;
    record_array += "{";
    for (int i = 0; i < dimension; i++)
    {
        count += records[pose_index][i];
    }

    // check if all variables are zeros.
    if (count == 0)
    {
        return "0";
    }

    std::stringstream ss;

    for (int i = 0; i < dimension; i++)
    {
        float rec = records[pose_index][i];
        float var = rec / (float)count;

        ss << var;
        std::string normal = ss.str();
        record_array += normal;

        if (i == dimension - 1)
        {
            record_array += '}';

            continue;
        }

        record_array += ',';
        ss.str("");
    }
    return record_array;
}

10,0,0,0,0,0,0,-1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,8,8,9