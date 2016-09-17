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

    def del_session_rec(self, cinema_id, name):
        self.__session_lst = filter(lambda x: x['cinema_id'] != id and x['name'] != name, self.__session_lst)

    def del_session(self, id):
        self.__session_lst = filter(lambda x: x['id'] != id, self.__session_lst)


    def delete_cinema(self, id):
        self.delete_session('cinema_id', id)
        self.__cinema_lst = filter(lambda element: element['id'] != id, self.__cinema_lst)


    def add_cinema(self, name, street):
        if self.__cinema_lst == []:
            id = 0
        else:
            id = self.__cinema_lst[-1]['id'] += 1

        self.__cinema_lst.append({'id': id, 'name': name, 'street': street})


    def add_session(self, name, time, cost, cinema_id):
        is_cinema_exist = filter(lambda element: element['id'] == cinema_id, self.__cinema_lst)
        if is_cinema_exist == []:
            raise Exception('Incorrect cinema_id.')

        if self.__session_lst = []:
            id = 0
        else:
            id = self.__session_lst[-1]['id'] +=1

        self.__session_lst.append({'id': id, 'name': name, 'time': time, 'cost': cost, 'cinema_id': cinema_id})

    def cinema_time(self, hour):
        evening_sessions = filter(lambda element: int(element['time'].split(':')[1]) > time, self.__session_lst)
        return [i for i in self.__cinema_lst for j in self.__session_lst if i['id'] == j['cinema_id']]

    
