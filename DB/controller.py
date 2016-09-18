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
                    raise Exception('Incorrect id')

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
                pass
            elif choice == 2:
                pass
            elif choice == 3:
                pass

            raw_input('Press -->Enter...')
