#pragma once

#include <vector>
#include <algorithm>
#include <memory>

namespace svg {

/**
 * \interface IObserver
 * @brief For notifications
 */
class IObserver : std::enable_shared_from_this<IObserver>
{
public:
   std::shared_ptr<IObserver> GetPtr() 
   {
      return shared_from_this();
   }
   /**
    * @brief Update derived classes
    */
   virtual void Update() = 0;
   virtual ~IObserver() = default;
};

/**
 * \interface IObservable
 * @brief For monitoring
 */
class IObservable
{
public:
   /**
    * @brief Adding a new observer for notify
    * 
    * @param m_pObserver Smart pointer IObservable
    */
   void Subscribe(std::shared_ptr<IObserver> a_pObserver)
   {
      m_vObservers.push_back(a_pObserver);
   }

   /**
    * @brief Delete observer from subcribers
    * 
    * @param m_pObserver Smart pointer to IObservable
    */
   void Unsubscribe(std::shared_ptr<IObserver> a_pObserver) 
   {
      m_vObservers.erase(
         std::remove_if(
            m_vObservers.begin(),
            m_vObservers.end(),
            [&](const std::weak_ptr<IObserver>& wptr) 
            {
               return wptr.expired() || wptr.lock() == a_pObserver;
            }
         ),
      m_vObservers.end());
   }
   /**
    * @brief Notify all observers
    */
   void NotifyUpdate()
   {
      for ( auto wptr : m_vObservers ) {
         if ( !wptr.expired() ) {
            auto observer = wptr.lock();
            observer->Update();
        }
      }
   }

   virtual ~IObservable() = default;
private:
   std::vector<std::weak_ptr<IObserver>> m_vObservers;
};

} /* end svg::*/