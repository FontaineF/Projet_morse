//Code le message en entrée dans le fichier .wav entré

#include<iostream>
#include<stdio.h>
#include<string.h>
#include <cmath>
#include <fstream>
#include<map>
using namespace std;

namespace little_endian_io
{
  template <typename Word>
  std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
  {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  }
}
using namespace little_endian_io;

char alphaa[37]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0','_'};
std::string morss[37]={{".-"},{"-..."},{"-.-."},{"-.."},{"."},{"..-."},{"--."},{"...."},{".."},{".---"},{"-.-"},{".-.."},{"--"},{"-."},{"---"},{".--."},{"--.-"},{".-."},{"..."},{"-"},{"..-"},{"...-"},{".--"},{"-..-"},{"-.--"},{"--.."},{".----"},{"..---"},{"...--"},{"....-"},{"....."},{"-...."},{"--..."},{"---.."},{"---."},{"-----"},{"/"}};


void saisie_t(){

    //on définit le dictionnaire que l'on va utiliser
    std::map<char, std::string> dct;
    for(int it = 0; it<38; it++){
        dct[alphaa[it]]=morss[it];
    }
    

    printf("\t\t\t* Codage d'un texte en morse (écrivez '_' en guise d'espace) *\n\n");
    
    std::string nom_de_fichier_wav;
    std::cout << "Quel nom voulez-vous donner au fichier ?" << std::endl;
    std::cout << "(par exemple : 'message_code')\n" << "  ->  ";
    std::cin >> nom_de_fichier_wav;
    std::cout << std::endl;

    std::cout << "ok\n\n\n";


    ofstream f( nom_de_fichier_wav + ".wav", ios::binary );

    // Write the file headers
    f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
    write_word( f,     16, 4 );  // no extension data
    write_word( f,      1, 2 );  // PCM - integer samples
    write_word( f,      2, 2 );  // two channels (stereo file)
    write_word( f,  44100, 4 );  // samples per second (Hz)
    write_word( f, 176400, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
    write_word( f,      4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
    write_word( f,     16, 2 );  // number of bits per sample (use a multiple of 8)

    // Write the data chunk header
    size_t data_chunk_pos = f.tellp();
    f << "data----";  // (chunk size to be filled in later)
  
    // Write the audio samples
    constexpr double two_pi = 6.283185307179586476925286766559;
    constexpr double max_amplitude = 32760;  // "volume"

    double hz        = 44100;    // samples per second
    double frequency = 261.626;  // middle C
    double seconds   = 0.2;      // time

    int N = hz * seconds;  // total number of samples

    write_word( f, 80, 400000 ); //silence initial
    char c[200]; //un message de taille maximale 200
    for(int k = 0; k<200; k++){
        c[k]='&';
    }
    std::cout << "\tVeuillez entrer votre message\n";
    std::cout << "  ->  ";
    std::cin >> c;
    std::cout << std::endl;
    int i=0;
    while(i<200){
        if (c[i]=='&'){
            i=200;
        }     
        if( dct.find(c[i]) != dct.end()){
            string mor = dct[c[i]];
                write_word( f, 80, 20*N ); //Silence avant une lettre
                for(const char &x : mor){
                    if(x=='.'){
                        for(int n=0; n<N; n++){
                            double value     = sin( (two_pi * n * frequency) / hz );
                            write_word( f, (int)(max_amplitude*value), 2);
                        }
                    }
                    if(x=='-'){
                        for(int n=0; n<3*N; n++){
                            double value     = sin( (two_pi * n * frequency) / hz );
                            write_word( f, (int)(max_amplitude*value), 2);
                        }
                    }
                    if(x=='/'){
                        write_word( f, 80, 20*N );
                    }                    
                    write_word( f, 80, 10*N ); //Silence entre deux signaux d'une lettre
                }
            }
        i += 1;
    }

    // (We'll need the final file size to fix the chunk sizes above)
    size_t file_length = f.tellp();

    // Fix the data chunk header to contain the data size
    f.seekp( data_chunk_pos + 4 );
    write_word( f, file_length - data_chunk_pos + 8 );

    // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
    f.seekp( 0 + 4 );
    write_word( f, file_length - 8, 4 ); 
}