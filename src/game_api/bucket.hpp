#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>

using BucketItem = std::variant<bool, int64_t, float, std::string>;
using KEY = int64_t;

struct Overlunky
{
    /// Current Overlunky options. Read only.
    std::map<std::string, BucketItem> options;
    /// Write some select options here to change Overlunky options. Just use the same keys as in options.
    std::map<std::string, BucketItem> set_options;
    /// Current Overlunky key bindings. Read only. You can use this to bind some custom feature to the same unknown key as currently bound by the user.
    std::map<std::string, KEY> keys;
    /// Disable some key bindings in Overlunky, whatever key they are actually bound to. Remember this might not be bound to the default any more, so only use this if you also plan on overriding the current keybinding, or just need to disable some feature and don't care what key it is bound on.
    std::unordered_set<std::string> ignore_keys;
    /// Disable keys that may or may not be used by Overlunky. You should probably write the keycodes you need here just in case if you think using OL will interfere with your keybinds.
    std::unordered_set<KEY> ignore_keycodes;
    /// TODO: Disable Overlunky features. Doesn't do anything yet.
    std::unordered_set<std::string> ignore_features;
};

class Bucket
{
  public:
    static Bucket* get();

    /// You can store arbitrary simple values here in Playlunky to be read in on Overlunky script for example.
    std::unordered_map<std::string, BucketItem> data;
    /// Access Overlunky options here, nil if Overlunky is not loaded.
    Overlunky* overlunky{nullptr};
};
