import pickle

class Model:

    def __init__(self, file_name):
        self.__cinema_lst = []
        self.__session_lst = []
        self.load(file_name)

    def load(self, file_name):
        try:
            with open(file_name, 'rb') as f:
                self.__cinema_lst, self.__session_lst = pickle.load(f)
        except:
            self.__cinema_lst = []
            self.__session_lst = []


    def save(self, file_name):
        with open(file_name, 'wb') as f:
            pickle.dump([__cinema_lst, __session_lst], f)


    def delete_session(self, key, value):
        self.__session_lst = filter(lambda element: element['key'] != value, self.__session_lst)



    #def delete_session(arg):
        #pass
