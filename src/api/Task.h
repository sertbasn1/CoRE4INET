//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef TASK_H_
#define TASK_H_

#include <cobject.h>


namespace TTEthernetModel {

typedef void(*cbFunc)(void *);

/**
 * @brief Class representing a Task.
 *
 * The class stores a funtion pointer and args and invokes the function periodically.
 *
 * @todo This may be merged with the Callback class in a joined superclass. The
 * code seems identical.
 *
 * @sa ApplicationBase
 *
 *  @author Till Steinbach
 */
class Task
{
    protected:
        /**
         * @brief Function pointer of the task.
         */
        void (*fn)(void *);
        /**
         * @brief Pointer to the function args.
         */
        void *arg;
        /**
         * @brief Boolean indicating whether args were set.
         */
        bool argSet;
    public:
        /**
         * @brief Constructor
         */
        Task(){
            argSet=false;
        }

        /**
         * @brief Setter for the function pointer.
         *
         * @param functionPointer the funtion pointer to be invoked in the task
         */
        virtual void setFunctionPointer(void (*functionPointer)(void*)){
            fn=functionPointer;
        }

        /**
         * @brief Getter for the function pointer.
         *
         * @return the funtion pointer that is invoked in the task
         */
        virtual cbFunc getFunctionPointer(){
            return fn;
        }

        /**
         * @brief Setter for the function args.
         *
         * @param setFunctionArg the funtion arg to be used in the task
         */
        virtual void setFunctionArg(void *setFunctionArg){
            arg=setFunctionArg;
            argSet=true;
        }

        /**
         * @brief Getter for the function args.
         *
         * @return the funtion arg used in the task
         */
        virtual void* getFunctionArg(){
            return arg;
        }

        /**
         * @brief execution of the task.
         *
         * If method is called the stored function pointer is invoked.
         */
        virtual void executeTask(){
            fn(arg);
        }
};

/**
 * @brief Class representing a Task especially for API.
 *
 * @sa Task
 */
class APITask : public Task
{
};

}

#endif /* TASK_H_ */
