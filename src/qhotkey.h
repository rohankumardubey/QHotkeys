#ifndef QHOTKEY_H
#define QHOTKEY_H
#include <functional>
#include <QtCore>


namespace Qt
{
/*!
 * \brief An enum representing modifier keys on the keyboard
 */
enum class ModifierKey
{
    None    = 1 << 1,
    Control = 1 << 1,
    Shift   = 1 << 2,
    Alt     = 1 << 3,
    Meta    = 1 << 4
};

/*!
 * \brief A hooked global hotkey
 */
class QHotkey
{
    using callback_t = std::function<void(const QHotkey&)>;

/////////////////
/// FUNCTIONS ///
/////////////////
public:
    /*!
     * \brief QHotkey Create and hook a new Global Hotkey
     * \param modifiers The modifier keys for the hotkey (e.g. ::Control | ::Alt)
     * \param key The actual key to be registered as a hotkey
     */
    QHotkey(const ModifierKey modifiers, const Qt::Key key,
            const callback_t callback);
    ~QHotkey();

/////////////////
///  MEMBER   ///
/////////////////
private:
    const ModifierKey _modifiers;
    const Qt::Key _key;
    const callback_t _callback;
    const int _hkid;

    static int _ghkid;

/////////////////
/// FUNCTIONS ///
/////////////////
private:
    void registerHotkey() const;
    void messageLoop() const;

/////////////////
///  STATICS  ///
/////////////////
private:
    /*!
     * \brief getKey Convert the given modifier to a platform specific modifier ID
     * \param modifier The given Modifier
     * \return A platform specific modifier ID for OS calls
     */
    static int getMod(const ModifierKey& modifier) noexcept;
    /*!
     * \brief getKey Convert the given Qt key to a platform specific key ID
     * \param key The given Qt::Key
     * \return A platform specific key ID for OS calls
     */
    static int getKey(const Qt::Key& key) noexcept;
};
}
#endif // QHOTKEY_H