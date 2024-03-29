// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_RESOURCEDB_RESOURCEDB_H_
#define FLATBUFFERS_GENERATED_RESOURCEDB_RESOURCEDB_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

namespace ResourceDB {

struct Texture;
struct TextureBuilder;

struct Sprite;
struct SpriteBuilder;

struct Sound;
struct SoundBuilder;

struct Font;
struct FontBuilder;

struct Text;
struct TextBuilder;

struct TextStream;
struct TextStreamBuilder;

struct Root;
struct RootBuilder;

struct Texture FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef TextureBuilder Builder;
  static FLATBUFFERS_CONSTEXPR_CPP11 const char *GetFullyQualifiedName() {
    return "ResourceDB.Texture";
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_PATH = 6
  };
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  bool KeyCompareLessThan(const Texture * const o) const {
    return *name() < *o->name();
  }
  int KeyCompareWithValue(const char *_name) const {
    return strcmp(name()->c_str(), _name);
  }
  const ::flatbuffers::String *path() const {
    return GetPointer<const ::flatbuffers::String *>(VT_PATH);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_PATH) &&
           verifier.VerifyString(path()) &&
           verifier.EndTable();
  }
};

struct TextureBuilder {
  typedef Texture Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(Texture::VT_NAME, name);
  }
  void add_path(::flatbuffers::Offset<::flatbuffers::String> path) {
    fbb_.AddOffset(Texture::VT_PATH, path);
  }
  explicit TextureBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Texture> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Texture>(end);
    fbb_.Required(o, Texture::VT_NAME);
    return o;
  }
};

inline ::flatbuffers::Offset<Texture> CreateTexture(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0,
    ::flatbuffers::Offset<::flatbuffers::String> path = 0) {
  TextureBuilder builder_(_fbb);
  builder_.add_path(path);
  builder_.add_name(name);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Texture> CreateTextureDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const char *path = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto path__ = path ? _fbb.CreateString(path) : 0;
  return ResourceDB::CreateTexture(
      _fbb,
      name__,
      path__);
}

struct Sprite FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef SpriteBuilder Builder;
  static FLATBUFFERS_CONSTEXPR_CPP11 const char *GetFullyQualifiedName() {
    return "ResourceDB.Sprite";
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_PATH = 6,
    VT_ELEMENTS = 8,
    VT_PADDING = 10,
    VT_WIDTH = 12,
    VT_HEIGHT = 14
  };
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  bool KeyCompareLessThan(const Sprite * const o) const {
    return *name() < *o->name();
  }
  int KeyCompareWithValue(const char *_name) const {
    return strcmp(name()->c_str(), _name);
  }
  const ::flatbuffers::String *path() const {
    return GetPointer<const ::flatbuffers::String *>(VT_PATH);
  }
  int32_t elements() const {
    return GetField<int32_t>(VT_ELEMENTS, 0);
  }
  int32_t padding() const {
    return GetField<int32_t>(VT_PADDING, 0);
  }
  int32_t width() const {
    return GetField<int32_t>(VT_WIDTH, 0);
  }
  int32_t height() const {
    return GetField<int32_t>(VT_HEIGHT, 0);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_PATH) &&
           verifier.VerifyString(path()) &&
           VerifyField<int32_t>(verifier, VT_ELEMENTS, 4) &&
           VerifyField<int32_t>(verifier, VT_PADDING, 4) &&
           VerifyField<int32_t>(verifier, VT_WIDTH, 4) &&
           VerifyField<int32_t>(verifier, VT_HEIGHT, 4) &&
           verifier.EndTable();
  }
};

struct SpriteBuilder {
  typedef Sprite Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(Sprite::VT_NAME, name);
  }
  void add_path(::flatbuffers::Offset<::flatbuffers::String> path) {
    fbb_.AddOffset(Sprite::VT_PATH, path);
  }
  void add_elements(int32_t elements) {
    fbb_.AddElement<int32_t>(Sprite::VT_ELEMENTS, elements, 0);
  }
  void add_padding(int32_t padding) {
    fbb_.AddElement<int32_t>(Sprite::VT_PADDING, padding, 0);
  }
  void add_width(int32_t width) {
    fbb_.AddElement<int32_t>(Sprite::VT_WIDTH, width, 0);
  }
  void add_height(int32_t height) {
    fbb_.AddElement<int32_t>(Sprite::VT_HEIGHT, height, 0);
  }
  explicit SpriteBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Sprite> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Sprite>(end);
    fbb_.Required(o, Sprite::VT_NAME);
    return o;
  }
};

inline ::flatbuffers::Offset<Sprite> CreateSprite(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0,
    ::flatbuffers::Offset<::flatbuffers::String> path = 0,
    int32_t elements = 0,
    int32_t padding = 0,
    int32_t width = 0,
    int32_t height = 0) {
  SpriteBuilder builder_(_fbb);
  builder_.add_height(height);
  builder_.add_width(width);
  builder_.add_padding(padding);
  builder_.add_elements(elements);
  builder_.add_path(path);
  builder_.add_name(name);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Sprite> CreateSpriteDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const char *path = nullptr,
    int32_t elements = 0,
    int32_t padding = 0,
    int32_t width = 0,
    int32_t height = 0) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto path__ = path ? _fbb.CreateString(path) : 0;
  return ResourceDB::CreateSprite(
      _fbb,
      name__,
      path__,
      elements,
      padding,
      width,
      height);
}

struct Sound FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef SoundBuilder Builder;
  static FLATBUFFERS_CONSTEXPR_CPP11 const char *GetFullyQualifiedName() {
    return "ResourceDB.Sound";
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_PATH = 6
  };
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  bool KeyCompareLessThan(const Sound * const o) const {
    return *name() < *o->name();
  }
  int KeyCompareWithValue(const char *_name) const {
    return strcmp(name()->c_str(), _name);
  }
  const ::flatbuffers::String *path() const {
    return GetPointer<const ::flatbuffers::String *>(VT_PATH);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_PATH) &&
           verifier.VerifyString(path()) &&
           verifier.EndTable();
  }
};

struct SoundBuilder {
  typedef Sound Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(Sound::VT_NAME, name);
  }
  void add_path(::flatbuffers::Offset<::flatbuffers::String> path) {
    fbb_.AddOffset(Sound::VT_PATH, path);
  }
  explicit SoundBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Sound> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Sound>(end);
    fbb_.Required(o, Sound::VT_NAME);
    return o;
  }
};

inline ::flatbuffers::Offset<Sound> CreateSound(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0,
    ::flatbuffers::Offset<::flatbuffers::String> path = 0) {
  SoundBuilder builder_(_fbb);
  builder_.add_path(path);
  builder_.add_name(name);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Sound> CreateSoundDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const char *path = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto path__ = path ? _fbb.CreateString(path) : 0;
  return ResourceDB::CreateSound(
      _fbb,
      name__,
      path__);
}

struct Font FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef FontBuilder Builder;
  static FLATBUFFERS_CONSTEXPR_CPP11 const char *GetFullyQualifiedName() {
    return "ResourceDB.Font";
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_PATH = 6,
    VT_POINT_SIZE = 8
  };
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  bool KeyCompareLessThan(const Font * const o) const {
    return *name() < *o->name();
  }
  int KeyCompareWithValue(const char *_name) const {
    return strcmp(name()->c_str(), _name);
  }
  const ::flatbuffers::String *path() const {
    return GetPointer<const ::flatbuffers::String *>(VT_PATH);
  }
  int32_t point_size() const {
    return GetField<int32_t>(VT_POINT_SIZE, 0);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_PATH) &&
           verifier.VerifyString(path()) &&
           VerifyField<int32_t>(verifier, VT_POINT_SIZE, 4) &&
           verifier.EndTable();
  }
};

struct FontBuilder {
  typedef Font Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(Font::VT_NAME, name);
  }
  void add_path(::flatbuffers::Offset<::flatbuffers::String> path) {
    fbb_.AddOffset(Font::VT_PATH, path);
  }
  void add_point_size(int32_t point_size) {
    fbb_.AddElement<int32_t>(Font::VT_POINT_SIZE, point_size, 0);
  }
  explicit FontBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Font> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Font>(end);
    fbb_.Required(o, Font::VT_NAME);
    return o;
  }
};

inline ::flatbuffers::Offset<Font> CreateFont(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0,
    ::flatbuffers::Offset<::flatbuffers::String> path = 0,
    int32_t point_size = 0) {
  FontBuilder builder_(_fbb);
  builder_.add_point_size(point_size);
  builder_.add_path(path);
  builder_.add_name(name);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Font> CreateFontDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const char *path = nullptr,
    int32_t point_size = 0) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto path__ = path ? _fbb.CreateString(path) : 0;
  return ResourceDB::CreateFont(
      _fbb,
      name__,
      path__,
      point_size);
}

struct Text FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef TextBuilder Builder;
  static FLATBUFFERS_CONSTEXPR_CPP11 const char *GetFullyQualifiedName() {
    return "ResourceDB.Text";
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_TEXT = 6
  };
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  bool KeyCompareLessThan(const Text * const o) const {
    return *name() < *o->name();
  }
  int KeyCompareWithValue(const char *_name) const {
    return strcmp(name()->c_str(), _name);
  }
  const ::flatbuffers::String *text() const {
    return GetPointer<const ::flatbuffers::String *>(VT_TEXT);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_TEXT) &&
           verifier.VerifyString(text()) &&
           verifier.EndTable();
  }
};

struct TextBuilder {
  typedef Text Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(Text::VT_NAME, name);
  }
  void add_text(::flatbuffers::Offset<::flatbuffers::String> text) {
    fbb_.AddOffset(Text::VT_TEXT, text);
  }
  explicit TextBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Text> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Text>(end);
    fbb_.Required(o, Text::VT_NAME);
    return o;
  }
};

inline ::flatbuffers::Offset<Text> CreateText(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0,
    ::flatbuffers::Offset<::flatbuffers::String> text = 0) {
  TextBuilder builder_(_fbb);
  builder_.add_text(text);
  builder_.add_name(name);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Text> CreateTextDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const char *text = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto text__ = text ? _fbb.CreateString(text) : 0;
  return ResourceDB::CreateText(
      _fbb,
      name__,
      text__);
}

struct TextStream FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef TextStreamBuilder Builder;
  static FLATBUFFERS_CONSTEXPR_CPP11 const char *GetFullyQualifiedName() {
    return "ResourceDB.TextStream";
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4
  };
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  bool KeyCompareLessThan(const TextStream * const o) const {
    return *name() < *o->name();
  }
  int KeyCompareWithValue(const char *_name) const {
    return strcmp(name()->c_str(), _name);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
};

struct TextStreamBuilder {
  typedef TextStream Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(TextStream::VT_NAME, name);
  }
  explicit TextStreamBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<TextStream> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<TextStream>(end);
    fbb_.Required(o, TextStream::VT_NAME);
    return o;
  }
};

inline ::flatbuffers::Offset<TextStream> CreateTextStream(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0) {
  TextStreamBuilder builder_(_fbb);
  builder_.add_name(name);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<TextStream> CreateTextStreamDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return ResourceDB::CreateTextStream(
      _fbb,
      name__);
}

struct Root FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef RootBuilder Builder;
  static FLATBUFFERS_CONSTEXPR_CPP11 const char *GetFullyQualifiedName() {
    return "ResourceDB.Root";
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_TEXTURES = 6,
    VT_SPRITES = 8,
    VT_SOUNDS = 10,
    VT_FONTS = 12,
    VT_TEXTS = 14,
    VT_TEXT_STREAMS = 16
  };
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Texture>> *textures() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Texture>> *>(VT_TEXTURES);
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Sprite>> *sprites() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Sprite>> *>(VT_SPRITES);
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Sound>> *sounds() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Sound>> *>(VT_SOUNDS);
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Font>> *fonts() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Font>> *>(VT_FONTS);
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Text>> *texts() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Text>> *>(VT_TEXTS);
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::TextStream>> *text_streams() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::TextStream>> *>(VT_TEXT_STREAMS);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_TEXTURES) &&
           verifier.VerifyVector(textures()) &&
           verifier.VerifyVectorOfTables(textures()) &&
           VerifyOffset(verifier, VT_SPRITES) &&
           verifier.VerifyVector(sprites()) &&
           verifier.VerifyVectorOfTables(sprites()) &&
           VerifyOffset(verifier, VT_SOUNDS) &&
           verifier.VerifyVector(sounds()) &&
           verifier.VerifyVectorOfTables(sounds()) &&
           VerifyOffset(verifier, VT_FONTS) &&
           verifier.VerifyVector(fonts()) &&
           verifier.VerifyVectorOfTables(fonts()) &&
           VerifyOffset(verifier, VT_TEXTS) &&
           verifier.VerifyVector(texts()) &&
           verifier.VerifyVectorOfTables(texts()) &&
           VerifyOffset(verifier, VT_TEXT_STREAMS) &&
           verifier.VerifyVector(text_streams()) &&
           verifier.VerifyVectorOfTables(text_streams()) &&
           verifier.EndTable();
  }
};

struct RootBuilder {
  typedef Root Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(Root::VT_NAME, name);
  }
  void add_textures(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Texture>>> textures) {
    fbb_.AddOffset(Root::VT_TEXTURES, textures);
  }
  void add_sprites(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Sprite>>> sprites) {
    fbb_.AddOffset(Root::VT_SPRITES, sprites);
  }
  void add_sounds(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Sound>>> sounds) {
    fbb_.AddOffset(Root::VT_SOUNDS, sounds);
  }
  void add_fonts(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Font>>> fonts) {
    fbb_.AddOffset(Root::VT_FONTS, fonts);
  }
  void add_texts(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Text>>> texts) {
    fbb_.AddOffset(Root::VT_TEXTS, texts);
  }
  void add_text_streams(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::TextStream>>> text_streams) {
    fbb_.AddOffset(Root::VT_TEXT_STREAMS, text_streams);
  }
  explicit RootBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Root> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Root>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Root> CreateRoot(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Texture>>> textures = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Sprite>>> sprites = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Sound>>> sounds = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Font>>> fonts = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::Text>>> texts = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ResourceDB::TextStream>>> text_streams = 0) {
  RootBuilder builder_(_fbb);
  builder_.add_text_streams(text_streams);
  builder_.add_texts(texts);
  builder_.add_fonts(fonts);
  builder_.add_sounds(sounds);
  builder_.add_sprites(sprites);
  builder_.add_textures(textures);
  builder_.add_name(name);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Root> CreateRootDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    std::vector<::flatbuffers::Offset<ResourceDB::Texture>> *textures = nullptr,
    std::vector<::flatbuffers::Offset<ResourceDB::Sprite>> *sprites = nullptr,
    std::vector<::flatbuffers::Offset<ResourceDB::Sound>> *sounds = nullptr,
    std::vector<::flatbuffers::Offset<ResourceDB::Font>> *fonts = nullptr,
    std::vector<::flatbuffers::Offset<ResourceDB::Text>> *texts = nullptr,
    std::vector<::flatbuffers::Offset<ResourceDB::TextStream>> *text_streams = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto textures__ = textures ? _fbb.CreateVectorOfSortedTables<ResourceDB::Texture>(textures) : 0;
  auto sprites__ = sprites ? _fbb.CreateVectorOfSortedTables<ResourceDB::Sprite>(sprites) : 0;
  auto sounds__ = sounds ? _fbb.CreateVectorOfSortedTables<ResourceDB::Sound>(sounds) : 0;
  auto fonts__ = fonts ? _fbb.CreateVectorOfSortedTables<ResourceDB::Font>(fonts) : 0;
  auto texts__ = texts ? _fbb.CreateVectorOfSortedTables<ResourceDB::Text>(texts) : 0;
  auto text_streams__ = text_streams ? _fbb.CreateVectorOfSortedTables<ResourceDB::TextStream>(text_streams) : 0;
  return ResourceDB::CreateRoot(
      _fbb,
      name__,
      textures__,
      sprites__,
      sounds__,
      fonts__,
      texts__,
      text_streams__);
}

inline const ResourceDB::Root *GetRoot(const void *buf) {
  return ::flatbuffers::GetRoot<ResourceDB::Root>(buf);
}

inline const ResourceDB::Root *GetSizePrefixedRoot(const void *buf) {
  return ::flatbuffers::GetSizePrefixedRoot<ResourceDB::Root>(buf);
}

inline const char *RootIdentifier() {
  return "2DSS";
}

inline bool RootBufferHasIdentifier(const void *buf) {
  return ::flatbuffers::BufferHasIdentifier(
      buf, RootIdentifier());
}

inline bool SizePrefixedRootBufferHasIdentifier(const void *buf) {
  return ::flatbuffers::BufferHasIdentifier(
      buf, RootIdentifier(), true);
}

inline bool VerifyRootBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<ResourceDB::Root>(RootIdentifier());
}

inline bool VerifySizePrefixedRootBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<ResourceDB::Root>(RootIdentifier());
}

inline const char *RootExtension() {
  return "bin";
}

inline void FinishRootBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<ResourceDB::Root> root) {
  fbb.Finish(root, RootIdentifier());
}

inline void FinishSizePrefixedRootBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<ResourceDB::Root> root) {
  fbb.FinishSizePrefixed(root, RootIdentifier());
}

}  // namespace ResourceDB

#endif  // FLATBUFFERS_GENERATED_RESOURCEDB_RESOURCEDB_H_
