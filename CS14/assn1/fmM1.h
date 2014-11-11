#ifndef FMT_H
#define FTM_H

// Name: Michael Uy
// SID: 861064409
// Date: 10/14/14
// Course: CS14
// Assn#: PS1



template<typename T>
void formatparagraph(std::ostream &os, const std::vector<T> &v, int width){
	int usedspace =0;
	for(int i=0; i<v.size();i++){
		//if it is too big, new line
		if(usedspace+converttostring(v[i]).size()>width){ 
			os<< std::endl;
			os<< converttostring(v[i]);
			usedspace=converttostring(v[i]).size()+1;
			os<< ' ';
		}
		//if if it fits
		else if(usedspace+converttostring(v[i]).size()<width){
		os<< converttostring(v[i]);
		os<< ' ';
		usedspace+=converttostring(v[i]).size()+1;
		}
		else if(usedspace+converttostring(v[i]).size()==width){
		os<< converttostring(v[i]);
		os<< std::endl;
		usedspace=0;
		}
	}
}





















#endif
