#include <iostream>
#include <vector>

using namespace std;

class Tweet;


class Usuario{
    private:
        string nome;
        string nome_usuario;
        vector<Usuario> seguidores;
        vector<Usuario> seguindo;


    public:
        Usuario();
        Usuario(string nome, string cpf) {this->nome = nome; this->nome_usuario = nome_usuario;}

        string getNome(){ return nome; }
        void setNome(string nome) { this->nome = nome; }

        string getNome_usuario(){ return nome_usuario; }
        void setNome_usuario(string nome_usuario) { this->nome_usuario = nome_usuario; }

        vector<Usuario> getSeguidores() { return seguidores; }
        void setSeguidores(vector<Usuario> _seguidores) { seguidores = _seguidores; }

        vector<Usuario> getSeguindo() { return seguindo; }
        void setSeguindo(vector<Usuario> _seguindo) { seguindo = _seguindo; }
        
        void postar_tweet(Tweet tweet);
        void seguir(Usuario _usuario);

};

class RedeSocial{
    private:
        vector<Usuario> usuarios;
        vector<Tweet> tweets;
    public:
        RedeSocial();
        RedeSocial(vector<Usuario>, vector<Tweet>);
        void registrarUsuario(string, string);
        Usuario buscarUsuario(string);
        vector<Usuario> listarUsuarios(){return usuarios;}
        vector<Tweet> listarTweets(){return tweets;}
};

int main(){

    return 0;
}

void  Usuario::postar_tweet(Tweet tweet){


}
void  Usuario::seguir(Usuario _usuario){

}

void RedeSocial::registrarUsuario(string nome, string nome_usuario){
    for(Usuario u : usuarios){
        if(u.getNome_usuario() == nome_usuario){
          cout<<"Já existe um usuario com este nome de usuario!"<<endl;
          return;  
        } 
    }
    Usuario usuario = Usuario(nome, nome_usuario);
    this->usuarios.push_back(usuario);
}

Usuario RedeSocial::buscarUsuario(string nomeUsuario){
    for(Usuario usuario : usuarios){
        if(usuario.getNome_usuario() == nomeUsuario) return usuario;
    }

    cout<<"Nao existe nenhum usuario com este nome de usuario!"<<endl;
    return Usuario();
}