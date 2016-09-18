from view import View
from model import Model

class Controller:

    def __init__(self, data_base):
        self.data = data_base

    def __cinema_controller(self):
        choice = -1
        while choice != 5:
            try:
                choice = int(raw_input('Enter menu item:\n'))
            except ValueError:
                View.error_message('Incorrect value\n')

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
                self.model.cinema_time(18)

            raw_input('Press -->Enter...')

    def __session_controller(self):
        choice = -1
        while choice != 4:
            try:
                choice = int(raw_input('Enter menu item:\n'))
            except ValueError:
                View.error_message('Incorrect value\n')

            if choice == 1:
                try:
                    name = raw_input('Enter session name:\n')
                    cost = float(raw_input('Enter session cost:\n'))
                    cinema_id = int(raw_input('Enter cinema_id:\n'))
                    time = raw_input('Enter time(hour:minutes):\n')
                    self.model.is_time_correct(time)
                    self.model.add_session(name, time, cost, cinema_id)
                except ValueError:
                    View.error_message('Incorrect value')
                except Exception as e:
                    View.error_message(e.message)

                View.success_message('Item successfuly added!!!')

            elif choice == 2:
                try:
                    id = int(raw_input('Enter id:\n'))
                except ValueError:
                    View.error_message('Incorrect value')

                if not self.model.is_exist(id, self.get_sessions()):
                    View.error_message('Incorrect id')
                    return

                self.model.del_session(id)
                View.success_message('Item successfuly deleted')

            elif choice == 3:
                self.__session_update_controller()

            raw_input('Press -->Enter...')

        def __cinema_update_controller(self):
            pass
