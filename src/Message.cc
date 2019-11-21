

#include "Message.hh"

namespace octetos
{
namespace core
{
        
        Warning::Warning(const std::string& brief): Message(brief)
        {}
        
        
        Confirmation::Confirmation(const std::string& brief): Message(brief)
        {
                
        }
        
        
        
        
        
        std::string Message::getBrief() const throw()
        {
                return brief;
        }
        Message::Message(const std::string& brief)
        {
                this->brief = brief;
        }
        
        
        void ActivityProgress::addActivities(int activities)
        {
                this->activities += activities;
        }
        void ActivityProgress::step(const Error& msg)
        {
                steps++;
                add(msg);
        }
        void ActivityProgress::step(const Confirmation& msg)
        {
                steps++;
                add(msg);
        }
        
        ActivityProgress::ActivityProgress(int activities)
        {
                steps = 0;
                this->activities = activities;
        }

}
}
