import MySQLdb as mdb
import csv


class AbstractClass(object):

    def __init__(self, table_name, columns_list):
        self.__table_name = table_name
        self.__columns_name = columns_list

    def select_from(self, condition):
        try:
            connection = mdb.connect('localhost', 'root', 'vlad40000', 'vpdb')
            cursor = connection.cursor(mdb.cursors.DictCursor)
            cursor.execute("SELECT * FROM " + self.__table_name + " " + condition)
            return cursor.fetchall()
        except mdb.Error as e:
            print 'ERROR %d %s' % (e.args[0], e.args[1])
        finally:
            if connection:
                connection.close()

    def fetch_all(self):
        return self.select_from("")

    def load(self, file_name):
        try:
            connection = mdb.connect('localhost', 'root', 'vlad40000', 'vpdb')
            cursor = connection.cursor(mdb.cursors.DictCursor)
            cursor.execute("LOAD DATA INFILE " + "'" + file_name + "'" + " INTO TABLE " + self.__table_name +
                           " FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n'")
            cursor.commit()
        except mdb.Error as e:
            print 'ERROR %d %s' % (e.args[0], e.args[1])
        finally:
            if connection:
                connection.close()

    def insert(self, new_data):
        try:
            connection = mdb.connect('localhost', 'root', 'vlad40000', 'vpdb')
            cursor = connection.cursor(mdb.cursors.DictCursor)
            request = "INSERT INTO " + self.__table_name + "("
            values = "VALUES("
            for item in self.__columns_name:
                request += item + ","
                values += str(new_data[item]) + ","

            request = request[:-1] + ")"
            values = values[:-1] + ")"
            cursor.execute(request + values)
            cursor.commit()
        except mdb.Error as e:
            print 'ERROR %d %s' % (e.args[0], e.args[1])
        finally:
            if connection:
                connection.close()

    def update(self, id, new_data):
        try:
            connection = mdb.connect('localhost', 'root', 'vlad40000', 'vpdb')
            cursor = connection.cursor(mdb.cursors.DictCursor)

            request = "UPDATE " + self.__table_name  + " SET "
            for item in self.__columns_name:
                request += item + "=" + new_data[item] + ","

            request = request[:-1] + " WHERE id=" + id
            cursor.execute(request)
            cursor.commit()
        except mdb.Error as e:
            print 'ERROR %d %s' % (e.args[0], e.args[1])
        finally:
            if connection:
                connection.close()
        pass

    def delete(self, condition):
        try:
            connection = mdb.connect('localhost', 'root', 'vlad40000', 'vpdb')
            cursor = connection.cursor(mdb.cursors.DictCursor)
            cursor.execute("DELETE FROM " + self.__table_name + " " + condition)
            cursor.commit()
        except mdb.Error as e:
            print 'ERROR %d %s' % (e.args[0], e.args[1])
        finally:
            if connection:
                connection.close()

    def delete_all(self):
        self.delete("")

    def select_by_id(self, id):
        return self.select_from("WHERE id=" + str(id))

    def delete_by_id(self, id):
        self.delete("WHERE id=" + str(id))


class Order(AbstractClass):
    pass


class Product(AbstractClass):
    pass


class Stock(AbstractClass):
    pass


class Client(AbstractClass):
    pass
