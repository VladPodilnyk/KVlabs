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
            pickle.dump([self.__cinema_lst, self.__session_lst], f)


    def delete_session(self, key, value):
        self.__session_lst = filter(lambda element: element['key'] != value, self.__session_lst)

    def del_session_rec(self, cinema_id, name):
        self.__session_lst = filter(lambda x: x['cinema_id'] != cinema_id and x['name'] != name, self.__session_lst)

    def del_session(self, id):
        self.__session_lst = filter(lambda x: x['id'] != id, self.__session_lst)


    def delete_cinema(self, id):
        self.delete_session('cinema_id', id)
        self.__cinema_lst = filter(lambda element: element['id'] != id, self.__cinema_lst)


    def add_cinema(self, name, street):
        if self.__cinema_lst == []:
            id = 0
        else:
            id = self.__cinema_lst[-1]['id'] + 1

        self.__cinema_lst.append({'id': id, 'name': name, 'street': street})


    def add_session(self, name, time, cost, cinema_id):
        is_cinema_exist = filter(lambda element: element['id'] == cinema_id, self.__cinema_lst)
        if is_cinema_exist == []:
            raise Exception('Incorrect cinema_id.')

        if self.__session_lst == []:
            id = 0
        else:
            id = self.__session_lst[-1]['id'] + 1

        self.__session_lst.append({'id': id, 'name': name, 'time': time, 'cost': cost, 'cinema_id': cinema_id})

    def cinema_time(self, hour):
        evening_sessions = filter(lambda element: int(element['time'].split(':')[0]) > hour, self.__session_lst)
        return [i for i in self.__cinema_lst for j in self.__session_lst if i['id'] == j['cinema_id']]

    def is_exist(self, id, lst):
        item = filter(lambda x: x['id'] == id, lst)
        if item:
            return True
        return False

    def __find(self, id, lst):
        for item in lst:
            if item['id'] == id:
                return lst.index(item)

    def cinema_update(self, id, key, value):
        indx = self.__find(id, self.__cinema_lst)
        self.__cinema_lst[indx][key] = value

    def session_update(self, id, key, value):
        indx = self.__find(id, self.__session_lst)
        self.__session_lst[indx][key] = value

    def get_cinemas(self):
        return self.__cinema_lst

    def get_sessions(self):
        return self.__session_lst

    def is_time_correct(self, time):
        if ':' not in time:
            raise Exception('Incorrect record')

        try:
            hour = int(time.split(':')[0])
            minutes = int(time.split(':')[1])
        except ValueError:
            raise Exception('Incorrect record')

        if (hour >= 0 and hour <= 23) and (minutes >= 0 and minutes <= 59 ):
            return True
        else:
            raise Exception('Incorrect record')
