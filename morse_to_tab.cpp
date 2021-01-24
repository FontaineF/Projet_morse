//Convertit le fichier wav en un tableau de données qui sera traduit par la fonction tab_to_text

#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>


using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;

//Définition du format utilisé
typedef struct  WAV_HEADER
{
    /* RIFF Chunk Descriptor */
    uint8_t         RIFF[4];        // RIFF Header Magic header
    uint32_t        ChunkSize;      // RIFF Chunk Size
    uint8_t         WAVE[4];        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t         fmt[4];         // FMT header
    uint32_t        Subchunk1Size;  // Size of the fmt chunk
    uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
    uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
    uint32_t        bytesPerSec;    // bytes per second
    uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t        bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t         Subchunk2ID[4]; // "data"  string
    uint32_t        Subchunk2Size;  // Sampled data length
} wav_hdr;


int* decoder()
{
    wav_hdr wavHeader;
    int headerSize = sizeof(wav_hdr);
    int duree_point = 100; //en millisecondes

    const char* filePath;
    std::string input;
    std::cout << "Entrez le nom du fichier à décoder : " << std::endl;
    std::cout << "(par exemple : 'message_code')" << std::endl;
    std::cout << "  ->  ";
    cin >> input;
    cin.get();
    input += ".wav";
    filePath = input.c_str();
    

    FILE* wavFile = fopen(filePath, "r");
    if (wavFile == nullptr){
        fprintf(stderr, "Fichier inaccessible ou entée eronnée: %s\n", filePath);
        int* rip = nullptr;
        return rip;
    }

    //Read the header
    size_t bytesRead = fread(&wavHeader, 1, headerSize, wavFile);
    int* valeur = new int[10000]; //Tableau contenant les données à traduire plus tard
    if (bytesRead > 0)
    {
        int8_t* buffer = new int8_t[2];
        int k = 0;
        fseek(wavFile, wavHeader.bytesPerSec*duree_point*0.001/2,SEEK_CUR); //Permet d'éviter les zéros du sinus de l'amplitude
        //On va lire les données, échantillon par échantillon, correspondant à la durée d'un signal "."
        while ((bytesRead = fread(buffer, sizeof buffer[0], 2, wavFile)) > 0 ){
            if (((buffer[0] << 8) + buffer[1]) != 0){       //L'amplitude du signal est non nulle pour cet échantillon
                valeur[k] = 1;                              //Le tableau de valeurs enregistre qu'il y avait un signal
            }
            else{                                           //L'amplitude du signal est nulle pour cet échantillon
                valeur[k] = 0;                              //Le tableau de valeurs enregistre qu'il n'y avait pas de signal
            }
            k+=1;
            fseek(wavFile, wavHeader.bytesPerSec*duree_point*0.001 - 2*(sizeof buffer[0]), SEEK_CUR);   //On passe à l'échantillon suivant
        }
        cout << endl;
        delete [] buffer;
        buffer = nullptr;
    }

    
    fclose(wavFile);
    return valeur;
}
