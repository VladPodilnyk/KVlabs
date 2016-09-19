from view import View
from model import Model

class Controller:

    def __init__(self, data_base):
        self.model = data_base

    def __cinema_controller(self):
        choice = -1
        while choice != 6:
            View.cinemas_menu()
            try:
                choice = int(raw_input('Enter menu item:\n'))
            except ValueError:
                View.error_message('Incorrect value')

            if choice == 1:
                name = raw_input('Enter cinema name:\n')
                street = raw_input('Enter street:\n')
                self.model.add_cinema(name, street)
                View.success_message('Item successfuly added!!!')
            elif choice == 2:
                try:
                    id = int(raw_input('Enter id:\n'))
                except ValueError:
                    View.error_message('Incorrect value\n')

                if not  self.model.is_exist(id, self.model.get_cinemas()):
                    View.error_message('Incorrect id')
                    return

                self.model.delete_cinema(id)
                View.success_message('Item successfuly deleted!!!')

            elif choice == 3:
                self.__cinema_update_controller()

            elif choice == 4:
                View.display(self.model.cinema_time(18))

            elif choice == 5:
                View.display(self.model.get_cinemas())

        raw_input('Press -->Enter...\n')

    def __session_controller(self):
        choice = -1
        while choice != 5:
            View.sessions_menu()
            try:
                choice = int(raw_input('Enter menu item:\n'))
            except ValueError:
                View.error_message('Incorrect value')

            if choice == 1:
                try:
                    name = raw_input('Enter session name:\n')
                    cost = float(raw_input('Enter session cost:\n'))
                    cinema_id = int(raw_input('Enter cinema_id:\n'))
                    time = raw_input('Enter time(hour:minutes):\n')
                    self.model.is_time_correct(time)
                    self.model.add_session(name, time, cost, cinema_id)
                    View.success_message('Item successfuly added!!!')
                except ValueError:
                    View.error_message('Incorrect value')
                except Exception as e:
                    View.error_message(e.message)

            elif choice == 2:
                try:
                    id = int(raw_input('Enter id:\n'))
                except ValueError:
                    View.error_message('Incorrect value')

                if not self.model.is_exist(id, self.model.get_sessions()):
                    View.error_message('Incorrect id')
                    return

                self.model.del_session(id)
                View.success_message('Item successfuly deleted!!!')

            elif choice == 3:
                self.__session_update_controller()

            elif choice == 4:
                View.display(self.model.get_sessions())

        raw_input('Press -->Enter...\n')

    def __cinema_update_controller(self):
        choice = -1
        try:
            id = int(raw_input('Enter id:\n'))
        except ValueError:
            View.error_message('Incorrect value')

        if  not self.model.is_exist(id, self.model.get_cinemas()):
            View.error_message('Incorrect id')
            return

        while choice != 3:
            View.cinemas_update_menu()
            try:
                choice = int(raw_input('Enter menu item:\n'))
            except ValueError:
                View.error_message('Incorrect value')

            if choice == 1:
                name = raw_input('Enter new cinema name:\n')
                self.model.cinema_update(id, 'name', name)
                View.success_message('Item successfuly updated!!!')

            elif choice == 2:
                street = raw_input('Enter new street:\n')
                self.model.cinema_update(id, 'street', street)
                View.success_message('Item successfuly updated!!!')

            raw_input('Press -->Enter...\n')

    def __session_update_controller(self):
        choice = -1
        try:
            id = int(raw_input('Enter id:\n'))
        except ValueError:
            View.error_message('Incorrect value')

        if  not self.model.is_exist(id, self.model.get_sessions()):
            View.error_message('Incorrect id')
            return

        while choice != 4:
            View.sessions_update_menu()
            try:
                choice = int(raw_input('Enter menu item:\n'))
            except ValueError:
                View.error_message('Incorrect value')

            if choice == 1:
                name = raw_input('Enter new session name:\n')
                self.model.session_update(id, 'name', name)
                View.success_message('Item successfuly updated!!!')

            elif choice == 2:
                try:
                    time = raw_input('Enter time:\n')
                    self.model.is_time_correct(time)
                    self.model.session_update(id, 'time', time)
                    View.success_message('Item successfuly updated!!!')
                except Exception as e:
                    View.error_message(e.message)

            elif choice == 3:
                try:
                    cost = float(raw_input('Enter cost:\n'))
                    self.model.session_update(id, 'cost', cost)
                    View.success_message('Item successfuly updated!!!')
                except ValueError:
                    View.error_message('Incorrect value')

            raw_input('Press -->Enter...\n')

    def run(self):
        choice = -1
        while choice != 3:
            View.data_base_menu()
            try:
                choice = int(raw_input('Enter menu item:\n'))
            except ValueError:
                View.error_message('Incorrect value')

            if choice == 1:
                self.__cinema_controller()

            elif choice == 2:
                self.__session_controller()

        raw_input('Press -->Enter...')
        self.model.save('data.txt')
