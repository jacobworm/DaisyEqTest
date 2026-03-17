#include <iostream>
#include <vector>
#include <fstream>
#include "Equalizer.h"

int main(){

    const int fs=48000;
    const int N = fs;

    Equalizer equalizer;
    equalizer.Init(fs);
// USER PARAMETERS::::::::::::::::::::::
// band 0 is low shelving, band 5 i high shelving

    short band = 5;
    float gain_db = -6;
    float freq_hz = 8000;
    float q_value = 1;
// Setting equalizer
    equalizer.setParameter(band,PM_GAIN,gain_db);
    equalizer.setParameter(band,PM_FREQ,freq_hz);
    equalizer.setParameter(band,PM_Q,q_value);

// Impulse for test
    std::vector<float> impulse(N, 0.0f);
    std::vector<float> output(N,0.0f);
    impulse[0] = 1.0f;
    for (int i=0; i<N; i++){
        output[i] = equalizer.Process(impulse[i]);
    }
    std::string filename = "impulse_b" + std::to_string(band) + "_g" + std::to_string(gain_db) 
            + "_f" + std::to_string(freq_hz) + "_q" + std::to_string(q_value) + ".txt";
    std::ofstream file(filename);
    // file << "band: " << band << ", gain: " << gain_db << ", freq: " << freq_hz << ", q: " << q_value <<std::endl;
    for(int n = 0; n < N; n++){
        file << output[n] << std::endl;
    }
    file.close();
    std::cout <<"Impulse output written to file impulse_out.txt"<<std::endl;
    return 0;
}