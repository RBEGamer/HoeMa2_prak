#include "mat.h"


mat::mat(const int _dim_w, const int _dim_h){

    if(_dim_w <= 0){
        #ifdef MAT_WARNING
        std::cout << "MAT WARNING :" << "const sim failed DIM_W" << __FILE__  << ":" << __LINE__ << std::endl;
        #endif
        dim_w = 0;
    }{
        dim_w = _dim_w;
    }

    if(_dim_h <= 0){
#ifdef MAT_WARNING
        std::cout << "MAT WARNING :" << "const sim failed DIM_H" << __FILE__  << ":" << __LINE__ << std::endl;
#endif
        dim_h = 0;
    }{
        dim_h = _dim_h;
    }

    //NOW CREATE VECTOR
    for (int i = 0; i < dim_w; ++i) {
        vec tmp(dim_h);
        data_holder_mat.push_back(tmp);
    }

#ifdef MAT_INFO
std::cout << "MAT INIT WITH w:" << dim_w << " h:" << dim_h << " " << __FILE__ << ":" << __LINE__ << std::endl;
#endif
}


void mat::print(std::ofstream* _file, int _space){

    if(_file == nullptr){return;}

    *_file << " { ";
    for (int j = 0; j < dim_h; ++j) {
        for (int i = 0; i < dim_w; ++i) { //w
            *_file << data_holder_mat.at(i).at(j)<< ", ";
        }
        *_file << std::endl;
        for (int k = 0; k < _space*4; ++k) {
            *_file << " ";
        }

    }
    *_file << "}" << std::endl;
}




vec mat::operator*(vec& x){
#ifdef MAT_WARNING
    if(x.gsize() >= data_holder_mat.size()) {
        std::cout << "MAT WARNING :" << "const sim failed DIM_W" << __FILE__ << ":" << __LINE__ << std::endl;
    }
#endif
    vec res(x.gsize());
    for (int ah = 0; ah < dim_h; ++ah) {
        double sun = 0.0; //sum
        for (int aw = 0; aw < dim_w; ++aw) {
            for (int v = 0; v < x.gsize(); ++v) {
                sun += data_holder_mat.at(aw).at(ah)*x.at(v);
            }
        }
        res.set_value(ah,sun);
    }
return res;
}
mat mat::invers(){
    if(dim_w != 2 || dim_h != 2){
        std::cout << "inverse geht nicht" << dim_w << "h" << dim_h << std::endl;
        throw;
    }
   mat tmat(dim_w, dim_h);
    double mutliplikator = 1.0 / (
                                         get_val(0, 0)*get_val(1, 1)- //A*D
                                         get_val(1, 0)*get_val(1, 0)
                                 );
    tmat.set_val(0,0,get_val(1,1)*mutliplikator); //a = d
    tmat.set_val(1,0,-get_val(1,0)*mutliplikator); //b = -b
    tmat.set_val(0,1,-get_val(0,1)*mutliplikator); //c = -c
    tmat.set_val(1,1,get_val(0,0)*mutliplikator); //d = a
}



void mat::set_val(const int _w, const int _h, const double _val){
#ifdef MAT_WARNING
    if(_w >= dim_w || _h > dim_h) {
        std::cout << "MAT WARNING :" << "OUT OF RANGE" << __FILE__ << ":" << __LINE__ << std::endl;
    }
#endif

    data_holder_mat.at(_w).at(_h) = _val;
}


double mat::get_val(const int _w, const int _h){
#ifdef MAT_WARNING
    if(_w >= dim_w || _h > dim_h) {
        std::cout << "MAT WARNING :" << "OUT OF RANGE" << __FILE__ << ":" << __LINE__ << std::endl;
    }
#endif
return data_holder_mat.at(_w).at(_h);
}
